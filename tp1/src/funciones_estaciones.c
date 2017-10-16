#include "../includes/includes.h"
#include "../includes/variables.h"


void listar()
{
	//printf("%s\n", "EStoy en listar");
	char * index [] = {"Station ID", "Station", "??", "Fecha", "Temperatura", "Humedad", "Punto de rocio", "Precipitacion", "Velocidad del viento",
	                   "Direccion", "Rafaga Maxima", "Presion", "Radiacion Solar", "Temperatura del suelo1", "Temperatura del suelo2", "Temperatura del suelo3",
	                   "Humedad de suelo 1", "Humedad de suelo 2", "Humedad de suelo 3", "Humedad de hoja", "  ", " "
	                  };
	struct Datos_Estaciones data;
	FILE *f = fopen ( A_LISTAR, "w" );

	if ( f == NULL )
		{
			printf ( "Error opening file!\n" );
			exit ( 1 );
		}

	for ( int i = 0; i < num_estaciones; i = i + 1 )
		{
			fprintf ( f, "-----------------------------------------------------------\n" );
			printf ( "ESTACION:%s, ID: %u\n", estaciones[i].nombre,
			         estaciones[i].estacion_id );
			printf ( "Sensores Disponibles \n" );
			fprintf ( f, "ESTACION:%s, ID: %u\n", estaciones[i].nombre,
			          estaciones[i].estacion_id );
			fprintf ( f, "Sensores Disponibles \n" );
			fprintf ( f, "-----------------------------------------------------------\n" );
			data = estaciones[i].buffer[0];
			char buf[255];
			strftime ( buf, sizeof ( buf ), "%d %b %Y %H:%M", &data.fecha );

			for ( int j = 4; j < 12; j = j + 1 )
				{
					printf ( "%s:  %s  \n", index[j], "HAY DATOS" );
					fprintf ( f, "%s:  %s  \n", index[j], "HAY DATOS" );
				}

			if ( data.rad_solar == -1 )
				{
					printf ( "%s:  %s  \n", index[12], "NO HAY DATOS" );
					fprintf ( f, "%s:  %s  \n", index[12], "NO HAY DATOS" );
				}
			else
				{
					printf ( "%s:  %s  \n", index[12], "HAY DATOS" );
					fprintf ( f, "%s:  %s  \n", index[12], "HAY DATOS" );
				}

			if ( data.temp_suelo == -1 )
				{
					printf ( "%s:  %s  \n", index[13], "NO HAY DATOS" );
					fprintf ( f, "%s:  %s  \n", index[13], "NO HAY DATOS" );
				}
			else
				{
					printf ( "%s:  %s  \n", index[13], "HAY DATOS" );
					fprintf ( f, "%s:  %s  \n", index[13], "HAY DATOS" );
				}
			fprintf ( f, "\n" );
			printf("\n");
		}

	fclose ( f );
}

void promedio_variable ( char * variable )
{
	FILE *fp = fopen ( A_PROM_VAR, "w" );

	if ( fp == NULL )
		{
			printf ( "Error opening file!\n" );
			exit ( 1 );
		}
	else
		{
			fprintf ( fp, "Promedios de la Variable:   %s \n \n", variable);

			float acumulador = 0, contador = 0;

			for ( int i = 0; i < num_estaciones; i = i + 1 )
				{
					for ( int j = 0; j < estaciones[i].contador_datos; j = j + 1 )
						{
							if ( strcmp ( variable, "Temperatura" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].temp; }
							else if ( strcmp ( variable, "Humedad" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].hum; }
							else if ( strcmp ( variable, "Punto de rocio" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].pto_roc; }
							else if ( strcmp ( variable, "Precipitacion" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].precip; }
							else if ( strcmp ( variable, "Velocidad del viento" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].vel_viento; }
							else if ( strcmp ( variable, "Rafaga Maxima" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].raf_max; }
							else if ( strcmp ( variable, "Presion" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].presion; }
							else if ( strcmp ( variable, "Radiacion Solar" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].rad_solar; }
							else if ( strcmp ( variable, "Temperatura del suelo 1" ) == 0 ) { acumulador = acumulador + estaciones[i].buffer[j].temp_suelo; }
							else
								{
									perror ( "VARIABLE NO VALIDA" );
									return;
								}

							if ( acumulador < 0 ) { break; }

							contador = contador + 1;
						}

					if ( acumulador >= 0 ) { fprintf ( fp, "Estacion %s:   %.3f \n", estaciones[i].nombre, acumulador / contador ); } //promedio[i] = acumulador /contador;
					else {fprintf ( fp, "Estacion %s SIN DATOS \n", estaciones[i].nombre);}
					acumulador = 0;
					contador = 0;
				}

			fclose ( fp );
		}
}

void mensual_precipitacion ( unsigned int id_estacion )
{
	struct Estacion_Meteorologica station;
	

	if ( estacion_por_id ( id_estacion, &station ) == 0 )
		{
			perror ( "NUMERO DE ESTACION NO VALIDO" );
			return;
		}

	FILE *f = fopen ( A_MENSUAL_PRECIP, "w" );

	if ( f == NULL )
		{
			printf ( "Error opening file!\n" );
			exit ( 1 );
		}
	else
		{
			char * meses [] = {"ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", "JULIO",
						"AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"
	                  };
			int mes_actual;
			float acumulador = 0;
			mes_actual = station.buffer[0].fecha.tm_mon;

			for ( int i = 0; i < station.contador_datos; i = i + 1 )
				{
					int j = station.buffer[i].fecha.tm_mon;

					if ( j == mes_actual ) { acumulador = acumulador + station.buffer[i].precip; }
					else
						{
							if (acumulador == 0)
							{
								fprintf ( f, "Precipitacion del Mes %i - %s: %s \n", mes_actual, meses[j],"NO HAY INFORMACION" );
							} else {
								fprintf ( f, "Precipitacion del Mes %i - %s :   %.3f \n", mes_actual, meses[j], acumulador );
								mes_actual = j;
								acumulador = station.buffer[i].precip;
							}
						}
				}

			fprintf ( f, "Precipitacion del Mes %i - %s:  %.3f \n", mes_actual, meses[mes_actual], acumulador );

			//fprintf ( f, "Precipitacion del Mes %i :   %.3f \n", mes_actual, acumulador );
			fclose ( f );
		}

	//printf("MES %.3f\n", precip_mensual[1]);
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
			exit ( 1 );
		}
	else
		{
			int dia_actual;
			float acumulador = 0;
			dia_actual = station.buffer[0].fecha.tm_mday;

			for ( int i = 0; i < station.contador_datos; i = i + 1 )
				{
					int j = station.buffer[i].fecha.tm_mday;

					if ( j == dia_actual ) { acumulador = acumulador + station.buffer[i].precip; }
					else
						{
							fprintf ( f, "Precipitacion del Dia %i:   %.3f \n", dia_actual, acumulador );
							dia_actual = j;
							acumulador = station.buffer[i].precip;
						}
				}

			fprintf ( f, "Precipitacion del Dia %i:   %.3f \n", dia_actual, acumulador );
			fclose ( f );
		}
}


void descargar ( int id_estacion )
{
	struct Estacion_Meteorologica station;
	estacion_por_id ( id_estacion, &station );

	FILE *fp = fopen ( A_DESCARGAR, "w" );

	if ( fp == NULL )
	{
		printf ( "Error opening file!\n" );
		exit ( 1 );
	}
	else
	{
		fprintf ( fp, "DATOS DE LA ESTACION %s \n \n", station.nombre);

		for ( int i = 0; i < station.contador_datos; i = i + 1 )
		{
			char buf[255];
			strftime ( buf, sizeof ( buf ), "%d %b %Y %H:%M", &station.buffer[i].fecha );
			fprintf(fp, "Fecha:  %s\n", buf);					
			fprintf(fp, "Temperatura:  %.2f\n", station.buffer[i].temp);
			fprintf(fp, "Humedad:  %.2f\n", station.buffer[i].hum);
			fprintf(fp, "Punto de Rocio:  %.2f\n", station.buffer[i].pto_roc);
			fprintf(fp, "Velocidad Viento:  %.2f\n", station.buffer[i].vel_viento);
			fprintf(fp, "Precipitacion:  %.2f\n", station.buffer[i].precip);
			fprintf(fp, "Rafaga Maxima:  %.2f\n", station.buffer[i].raf_max);
			fprintf(fp, "Presion:  %.2f\n", station.buffer[i].presion);
			fprintf(fp, "Radiacion Solar:  %.2f\n", station.buffer[i].rad_solar);
			fprintf(fp, "Temperatura Suelo:  %.2f\n", station.buffer[i].temp_suelo);
			fprintf(fp, "Direccion Viento:  %s\n", station.buffer[i].dir_viento);
			fprintf(fp, "%s\n", "---------------------------------------------");

		}

		fclose ( fp );
	}

	return;
}


