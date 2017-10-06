/*! \file funciones_genericas.h
    \brief Este archivo contiene las funciones de lectura del archivo de datos meteorologicos
*/

#ifndef FUNCIONES_GENERICAS_H
#define FUNCIONES_GENERICAS_H


#include <arpa/inet.h>

char ** split_line(char * line);
void enviar_respuesta(int num_funcion);
int eleccion_funcion(char * funcion_elegida);
void print_file(char *nombre_archivo);



#endif