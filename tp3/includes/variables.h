/*! \file variables.h
    \brief Este archivo contiene las variables globales del programa
*/

#ifndef VARIABLES_H
#define VARIABLES_H

#define TAM 512

#include "../includes/includes.h"

#define A_LISTAR "../archivos/listar.txt"
#define A_PROM_VAR "../archivos/promedio_variable.txt"
#define A_MENSUAL_PRECIP "../archivos/mensual_precipitacion.txt"
#define A_DIARIO_PRECIP "../archivos/diario_precipitacion.txt"
#define A_DESCARGAR "../archivos/descargar.txt"

/*! \struct Datos_Estaciones
    \brief Almacena valores relacionados a una medicion de una estacion meteorologica


*/

struct Datos_Estaciones {
    struct tm fecha;
    float temp;
    float hum;
    float pto_roc;
    float vel_viento;
    float precip;
    float raf_max;
    float presion;
    float rad_solar;
    float temp_suelo;
    char dir_viento[20];

};  


/*! \struct Estacion_Meteorologica
    \brief Almacena los datos de una estacion meteorlogica y un buffer con todas sus mediciones 

*/

struct Estacion_Meteorologica{
    char nombre[100];
    unsigned int estacion_id;
    int contador_datos;
    struct Datos_Estaciones buffer[16000];

}; 



struct Estacion_Meteorologica estaciones[100];

int num_estaciones;

int estacion_por_id ( unsigned int id_estacion, struct Estacion_Meteorologica * station );
void print_aws_station ( struct Estacion_Meteorologica station );



#endif