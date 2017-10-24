#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <omp.h>


#define A_PULSO "archivos/pulsos.iq"
#define A_RESULTADOS "archivos/resultados.txt"
#define TAM 250
#define CANT_VSxP 250
#define MAX_DATOS_LECTURA 5000
#define TOTAL_GATES 500

struct Lectura{
	float lectura_i;
	float lectura_q;
};

struct Muestra
{
    struct Lectura lect_v;
    struct Lectura lect_h;
};


float valor_absoluto ( struct Lectura lect )
{

    return sqrt ( pow ( lect.lectura_i, 2 ) + pow (  lect.lectura_q, 2 ) );
}

int guardar_resultados(char * file_path, int cant_pulsos);


float autocorr_M_V [TOTAL_GATES];
float autocorr_M_H [TOTAL_GATES];

int main(int argc, char *argv[])
{
    if ( !argv[1] || !argv[2])
    {
        printf("%s\n", "Escriba ./ <nombre_del_programa> t [num_hilos]");
        return 0;
    }
    if ( !strcmp ( "t", argv[1] ) ) {omp_set_num_threads ( atoi ( argv[2] ) ); }
    else { omp_set_num_threads ( 1 ); }

    printf ( "%d \n", omp_get_max_threads());

    clock_t start, end;
    double cpu_time_used_lectura_pulsos, cpu_time_used_matrices, cpu_time_used_correlacion, cpu_time_used_total, cpu_time_used_cant_pulsos;



    FILE *fp;
    uint16_t vs_por_pulso[CANT_VSxP];

    int posicion_pulso[CANT_VSxP];
    int tamano_gate_por_pulso[CANT_VSxP];

    int cant_pulsos = 0;


    char *buffer;
    int tam_archivo, i, limite_gate = 0;
    long byte_leidos = 0;

    start = clock();
    
    fp = fopen(A_PULSO,"rb");  // r for read, b for binary

    if(fp == NULL)
    {
    	perror("Lectura de archivo: Error al abrir el archivo");
    	exit(1);
    }

    
    struct stat st;
    // stat(file_name, &st)
    fstat(fileno(fp), &st);;
    printf("Tamaño del archivo es %ld \n", st.st_size);
    tam_archivo = st.st_size;

    buffer = malloc(tam_archivo + 1);
    fread(buffer,tam_archivo,1,fp);
    fclose(fp);

    end = clock();
    cpu_time_used_lectura_pulsos = ((double) (end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for ( i = 0; byte_leidos < tam_archivo; i++ )
    {
    	posicion_pulso[i] = byte_leidos + sizeof ( uint16_t );
            //---- OBTENGO CANTIDAD DE MUESTRAS
    	memmove ( &vs_por_pulso[i], &buffer[byte_leidos], sizeof ( uint16_t ) );
            //--------ACTUALIZO PUNTERO
    	byte_leidos += sizeof ( uint16_t ) + 4 * vs_por_pulso[i] * sizeof (	float );
            //CALCULO EL TAMANO MINIMO DE UN GATE
        tamano_gate_por_pulso[i] = vs_por_pulso[i] / TOTAL_GATES;
            //---GUARDO UBICACION DEL PULSO
        cant_pulsos ++;
    }
    printf("%d\n", cant_pulsos);
    end = clock();
    cpu_time_used_cant_pulsos = ((double) (end - start)) / CLOCKS_PER_SEC;

    float M_v[cant_pulsos][TOTAL_GATES];
    float M_h[cant_pulsos][TOTAL_GATES];
    int ecuacion = 0;
    float val_abs_v = 0.0, val_abs_h = 0.0;

    byte_leidos = 0;
    start = clock();


    #pragma omp parallel for private(i,ecuacion , limite_gate, byte_leidos,val_abs_v,val_abs_h) shared(buffer,M_v,M_h, posicion_pulso)
    for ( i = 0; i < cant_pulsos; i++ )
    {
        //printf("%d\n", i);
        byte_leidos = 0;

        byte_leidos = posicion_pulso[i];

        ecuacion = vs_por_pulso[i] - tamano_gate_por_pulso[i] * TOTAL_GATES;//MAGIA

    	/* Todas las lecturas de un pulso */
        int cant = 0;
        limite_gate = 0;
        for (int k = 0; k < TOTAL_GATES; k++)
        {
            val_abs_v = 0.0;
            val_abs_h = 0.0;

            if ( k >= ecuacion ) { limite_gate = tamano_gate_por_pulso[i]; }
            else { limite_gate = tamano_gate_por_pulso[i] + 1; }


            for (int j = 0; j < limite_gate; ++j)
            {

                struct Muestra muestra_actual;
                memmove ( &muestra_actual, &buffer[byte_leidos], sizeof(struct Muestra) );

                val_abs_v = val_abs_v + valor_absoluto(muestra_actual.lect_v);
                val_abs_h = val_abs_h + valor_absoluto(muestra_actual.lect_h);

                byte_leidos += sizeof ( struct Muestra );

            }

            M_v[i][k] = val_abs_v / limite_gate;
            M_h[i][k] = val_abs_h / limite_gate;
            
            cant ++;
            
            
        }
        //printf("Pulsos Procesados: %d\n", i);

    }

    printf("%f\n", M_h[0][0]);
    end = clock();
    cpu_time_used_matrices = ((double) (end - start)) / CLOCKS_PER_SEC;


    float accumulador;
    start = clock();
    #pragma omp parallel sections
    {
        #pragma omp section
        for (int i = 0; i < TOTAL_GATES; ++i)
        {
            accumulador = 0;
            for (int j = 0; j < cant_pulsos; ++j)
            {
                accumulador += M_v[j][i] * M_h[j + 1][i];
            }
            autocorr_M_V[i] = accumulador / cant_pulsos;
        }
        #pragma omp section
        for (int i = 0; i < TOTAL_GATES; ++i)
        {
            accumulador = 0;
            for (int j = 0; j < cant_pulsos; ++j)
            {
                accumulador += M_h[j][i] * M_h[j + 1][i];
            }
            autocorr_M_H[i] = accumulador / cant_pulsos;
        }

    }
    

    end = clock();
    cpu_time_used_correlacion = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Tiempo lectura pulsos.iq %f \n", cpu_time_used_lectura_pulsos);
    printf("Tiempo Cantidad de pulsos %f \n", cpu_time_used_cant_pulsos);
    printf("Tiempo Formacion de Matriz pulso vs gate %f \n", cpu_time_used_matrices);
    printf("Tiempo Correlacion %f \n", cpu_time_used_correlacion);

    cpu_time_used_total = cpu_time_used_lectura_pulsos + cpu_time_used_cant_pulsos + cpu_time_used_matrices + cpu_time_used_correlacion;
    printf("Tiempo total de ejecucion %f \n", cpu_time_used_total);

    
    if(guardar_resultados(A_RESULTADOS, cant_pulsos) == 0){
        printf("%s\n", "Resultados Guardados correctamente");
        
    } else {
        return 1;
    }

    return 0;


}

int guardar_resultados(char * file_path, int cant_pulsos)
{
    FILE* f = fopen(file_path,"wb");
    int nro_gate = 0;

    if(!f){
        printf("Error abriendo archivo para escritura\n");
        return 1;
    }
    if(fwrite(&cant_pulsos, sizeof(int), 1, f) < 0){
        printf("Error fwrite\n");
        fclose(f);
        return 1;
    }
    /* Guardo todos los valores de la correlacion v*/
    for (int i = 0; i < TOTAL_GATES; ++i, nro_gate++)
    {

        if(fwrite(&nro_gate, sizeof(uint16_t), 1, f) < 0){
            printf("Error fwrite\n");
            fclose(f);
            return 1;
        }
        if(fwrite(&autocorr_M_V[nro_gate], sizeof(float), 1, f) < 0){
            printf("Error fwrite\n");
            fclose(f);
            return 1;
        }
        
    }

    nro_gate = 0;
    /* Guardo todos los valores de la correlacion h */
    for (int i = 0; i < TOTAL_GATES; ++i, nro_gate++)
    {
        if(fwrite(&nro_gate, sizeof(uint16_t), 1, f) < 0){
            printf("Error fwrite\n");
            fclose(f);
            return 1;
        }
        if(fwrite(&autocorr_M_H[nro_gate], sizeof(float), 1, f) < 0){
            printf("Error fwrite\n");
            fclose(f);
            return 1;
        }
    }
    fclose(f);


    return 0;
}
