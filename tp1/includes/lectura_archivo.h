/*! \file lectura_archivo.h
    \brief Este archivo contiene las funciones de lectura del archivo de datos meteorologicos
*/

#ifndef LECTURA_ARCHIVO_H
#define LECTURA_ARCHIVO_H

struct tm string_to_time ( char * str_to_tm );

struct Estacion_Meteorologica * get_estacion ( unsigned int id_estacion,
                                  char * nombre_estacion );


void setear_dato_a_estacion ( struct Estacion_Meteorologica * estacion, struct Datos_Estaciones dato_estacion );


int existe_estacion ( int id_estacion );



struct Datos_Estaciones crear_dato_estacion ( char * fecha, float temp, float hum,
                              float pto_roc, float precip, float vel_viento, char * dir_viento,
                              float raf_max,
                              float presion, float rad_solar, float temp_suelo );


void setear_datos ( char * line );


void cargar_archivo();




#endif