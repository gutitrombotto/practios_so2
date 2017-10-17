#include "../includes/includes.h"
#include "../includes/variables.h"

const char * table_header[] = {
	"<div class=\"container-fluid\">",
	"<div class=\"panel panel-default\">",
	"<div class=\"panel-heading\">",
	"<h4>Precipitaciones </h4>",
	"</div>",
	"<table class=\"table\">",
	"<thead>",
	"<tr>",
	"<th> Dia </th>",
	"<th> Precipitaci&oacuten [mm] </th>",
	"</tr>",
	"</thead>",
	"<tbody>",
	NULL
};

const char * table_mensual_header[] = {
	"<div class=\"container-fluid\">",
	"<div class=\"panel panel-default\">",
	"<div class=\"panel-heading\">",
	"<h4>Precipitaciones Mensuales </h4>",
	"</div>",
	"<table class=\"table\">",
	"<thead>",
	"<tr>",
	"<th> Mes </th>",
	"<th> Precipitaci&oacuten [mm] </th>",
	"</tr>",
	"</thead>",
	"<tbody>",
	NULL
};

const char * table_promedio_header[] = {
	"<div class=\"container-fluid\">",
	"<div class=\"panel panel-default\">",
	"<table class=\"table\">",
	"<thead>",
	"<tr>",
	"<th> Estacion </th>",
	"<th> Promedio </th>",
	"</tr>",
	"</thead>",
	"<tbody>",
	NULL
};


void print_table_header(FILE *f)
{
	for (int i = 0; table_header[i] != NULL ; ++i)
	{
		fprintf ( f, "%s", table_header[i] );
	}
	return;
}

void print_table_mes_header(FILE *f)
{
	for (int i = 0; table_mensual_header[i] != NULL ; ++i)
	{
		fprintf ( f, "%s", table_mensual_header[i] );
	}
	return;
}

void print_table_promedio_header(FILE *f)
{
	for (int i = 0; table_promedio_header[i] != NULL ; ++i)
	{
		fprintf ( f, "%s", table_promedio_header[i] );
	}
	return;
}
struct tm string_to_time ( char * str_to_tm )
{
    struct tm tm;
    memset ( &tm, 0, sizeof ( struct tm ) );
    strptime ( str_to_tm, "%d/%m/%Y %H:%M", &tm );
    return tm;
}

struct Estacion_Meteorologica * get_station ( unsigned int id_estacion,
                                  char * nombre_estacion )
{
    for ( int i = 0; i < num_estaciones; i = i + 1 )
        {
            if ( estaciones[i].estacion_id == id_estacion ) { return &estaciones[i]; }
        }

    estaciones[num_estaciones].estacion_id = id_estacion;
    strcpy ( estaciones[num_estaciones].nombre, ( const char * ) nombre_estacion );
    estaciones[num_estaciones].contador_datos = 0;
    num_estaciones = num_estaciones + 1;
    printf ( "%s :  %s\n", "NUEVA ESTACION", estaciones[num_estaciones - 1].nombre );
    return &estaciones[num_estaciones - 1];
}

void setear_dato_a_estacion ( struct Estacion_Meteorologica * station, struct Datos_Estaciones data )
{
    station->buffer[station->contador_datos] = data;
    station->contador_datos = station->contador_datos + 1;
    return;
}

int estacion_por_id ( unsigned int id_estacion, struct Estacion_Meteorologica * station )
{
    for ( int i = 0; i < num_estaciones; i = i + 1 )
        {
            if ( estaciones[i].estacion_id == id_estacion )
                {
                    *station = estaciones[i];
                    return 1;
                }
        }

    return 0;
}

int existe_estacion ( int id_estacion )
{
    for ( int i = 0; i < num_estaciones; i = i + 1 )
        {
            if ( estaciones[i].estacion_id == id_estacion )
                {
                    return id_estacion;
                }
        }

    return 0;
}



struct Datos_Estaciones crear_dato_estacion ( char * fecha, float temp, float hum,
                              float pto_roc, float precip, float vel_viento, char * dir_viento,
                              float raf_max,
                              float presion, float rad_solar, float temp_suelo )
{
    struct Datos_Estaciones data;
    data.fecha = string_to_time ( fecha );
    data.temp = temp;
    data.hum = hum;
    data.pto_roc = pto_roc;
    data.vel_viento = vel_viento;
    data.precip =  precip;
    data.raf_max = raf_max;
    data.presion = presion;
    data.rad_solar = rad_solar;
    data.temp_suelo = temp_suelo;
    //data.dir_viento = dir_viento;
    strcpy ( data.dir_viento, ( const char * ) dir_viento );
    return data;
}

void setear_datos ( char * line )
{
    char *token;
    unsigned int id_estacion;
    int line_counter = 0;
    char dir_viento[20];
    char * fecha;
    struct Datos_Estaciones data;
    struct Estacion_Meteorologica * station;
    float temp, hum, pto_roc, precip, vel_viento, raf_max, presion, rad_solar,
          temp_suelo;
    const char s[2] = ",";
    char *saveptr;
    token = strtok_r ( line, s, &saveptr );

    while ( token != NULL )
        {
            if ( line_counter == 0 )
                {
                    id_estacion = atoi ( token );
                }

            if ( line_counter == 1 ) { station = get_station ( id_estacion, token ); }

            if ( line_counter == 3 ) { fecha = token; }

            if ( line_counter == 4 ) { temp = atof ( token ); }

            if ( line_counter == 5 ) { hum = atof ( token ); }

            if ( line_counter == 6 ) { pto_roc = atof ( token ); }

            if ( line_counter == 7 ) { precip = atof ( token ); }

            if ( line_counter == 8 ) { vel_viento = atof ( token ); }

            if ( line_counter == 9 ) { strcpy ( dir_viento, ( const char * ) token ); }

            if ( line_counter == 10 ) { raf_max = atof ( token ); }

            if ( line_counter == 11 ) { presion = atof ( token ); }

            if ( line_counter == 12 )
                {
                    if ( strcmp ( "--", token ) == 0 ) { rad_solar = -1.0; }
                    else { rad_solar = atof ( token ); }
                }

            if ( line_counter == 13 )
                {
                    if  ( strcmp ( "--", token ) == 0 ) { temp_suelo = -1.0; }
                    else { temp_suelo = atof ( token ); }
                }

            line_counter = line_counter + 1;
            token = strtok_r ( NULL, s, &saveptr );
        }

    data = crear_dato_estacion ( fecha, temp, hum, pto_roc, precip, vel_viento,
                          dir_viento, raf_max, presion, rad_solar, temp_suelo );
    setear_dato_a_estacion ( station, data );
    //print_aws_station(*station);
}



void cargar_archivo(){
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    int lineas_innecesarias = 3;


    fp = fopen("../datos_meteorologicos.CSV", "r");
    //fp = fopen("../datos_meteorologicos_modif.csv", "r");

    if(NULL == fp)
    {
        perror("Lectura de archivo: Error al abrir el archivo");
        exit(0);
    }

    while (getline(&line, &len, fp)) {
        if (!lineas_innecesarias)    break;
        lineas_innecesarias = lineas_innecesarias - 1;
    }
    while((nread = getline(&line, &len, fp))!= -1){
    
        setear_datos(line);
    }
    free(line);
    fclose(fp);
}

	void diario_precipitacion ( unsigned int id_estacion )
	{
		struct Estacion_Meteorologica station;

		if ( estacion_por_id ( id_estacion, &station ) == 0 )
		{
			perror ( "NUMERO DE ESTACION NO VALIDO" );
			return;
		}

		FILE *f = fopen ( A_DIARIO_PRECIP, "w" );


		if ( f == NULL )
		{
			
			printf ( "Error opening file!\n" );
			//perror("FILE");
			exit ( 1 );
		}
		else
		{
			fprintf(f, "<h2 class=\"text-center\"> Estacion Meteorologica %s </h2>\n", station.nombre);
			print_table_header(f);
			int dia_actual;
			float acumulador = 0;
			dia_actual = station.buffer[0].fecha.tm_mday;

			for ( int i = 0; i < station.contador_datos; ++i )
			{
				int j = station.buffer[i].fecha.tm_mday;

				if ( j == dia_actual ) { acumulador = acumulador + station.buffer[i].precip; }
				else
				{
					fprintf(f, "<tr>\n");
					fprintf(f, "<td> %i </td> \n", dia_actual);
					fprintf(f, "<td> %.3f </td> \n", acumulador);
					fprintf(f, "</tr>\n");


							//fprintf ( f, "PRECIPITACIONES DIA %i --> %f \n", dia_actual, acumulador );
					dia_actual = j;
					acumulador = station.buffer[i].precip;
				}
			}
			fprintf(f, "<tr>\n");
			fprintf(f, "<td> %i </td> \n", dia_actual);
			fprintf(f, "<td> %f </td> \n", acumulador);
			fprintf(f, "</tr>\n");

			//fprintf ( f, "PRECIPITACIONES DIA %i --> %f \n", dia_actual, acumulador );
			fprintf(f, "</tbody></table></div></div>\n");
			fclose ( f );
		}
		fprintf(f, "</tbody></table></div></div>\n");

	}

int main(int argc, char const *argv[])
{
    cargar_archivo();
	diario_precipitacion(30135);
    return 0;
}
