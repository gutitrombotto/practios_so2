#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


#define A_PULSO "archivos/pulsos.iq"
#define TAM 250
#define CANT_VSxP 250
#define MAX_DATOS_LECTURA 5000
#define TOTAL_GATES 500

struct Lectura{
	float lectura_i;
	float lectura_q;
};
/*!< Estructura de una lectura compleja del radar, compuesta de un valor
en fase y otro en cuadratura. */

struct Pulso{
	int valid_samples;
	struct Lectura dato_v[MAX_DATOS_LECTURA];
	struct Lectura dato_h[MAX_DATOS_LECTURA];
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

int guardar_resultados(char * file_path);

int main(int argc, char *argv[])
{
	FILE *fp;
	uint16_t vs_por_pulso[CANT_VSxP];

	int posicion_pulso[CANT_VSxP];
    int tamano_gate_por_pulso[CANT_VSxP];

    int cant_pulsos = 0;


    char *buffer;
    int tam_archivo, i, limite_gate = 0;
    long byte_leidos = 0;
    float lectura[4*MAX_DATOS_LECTURA];
//	struct Lectura_por_Pulso lecturas_por_pulso[MAX_DATOS_LECTURA];

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

    float M_v[cant_pulsos][TOTAL_GATES];
    float M_h[cant_pulsos][TOTAL_GATES];


    byte_leidos = 0;

    for ( i = 0; i < cant_pulsos; i++ )
    {
        //printf("%d\n", i);
        byte_leidos = 0;

        byte_leidos = posicion_pulso[i];

        int diff = vs_por_pulso[i] - tamano_gate_por_pulso[i] * TOTAL_GATES;//MAGIA

    	/* Todas las lecturas de un pulso */
        int cant = 0;
        limite_gate = 0;
        for (int k = 0; k < TOTAL_GATES; k++)
        {
            float val_abs_v = 0.0, val_abs_h = 0.0;

            if ( k >= diff ) { limite_gate = tamano_gate_por_pulso[i]; }
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


    float autocorr_M_V [TOTAL_GATES];
    float autocorr_M_H [TOTAL_GATES];

    float accumulador;
    
    for (int i = 0; i < TOTAL_GATES; ++i)
    {
        accumulador = 0;
        for (int j = 0; j < cant_pulsos; ++j)
        {
            accumulador += M_v[j][i] * M_h[j + 1][i];
        }
        autocorr_M_V[i] = accumulador / cant_pulsos;
    }

    for (int i = 0; i < TOTAL_GATES; ++i)
    {
        accumulador = 0;
        for (int j = 0; j < cant_pulsos; ++j)
        {
            accumulador += M_h[j][i] * M_h[j + 1][i];
        }
        autocorr_M_H[i] = accumulador / cant_pulsos;
    }
     
    return 0;
}

int guardar_resultados(char * file_path)
{
    return 0;
}