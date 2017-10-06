/*! \file tools.h
    \brief Este archivo contiene herramientas de utilidad
*/

/*! \def MAX_BUFFER
    \brief Tamaño maximo del buffer donde se van a guardar los datos obtenidos en la funcion file_open
*/
#ifndef	TOOLS_H
#define	TOOLS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BUFFER 5000
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/*!	\fn void file_open(const char* path,char * buffer)
	\brief Leer un archivo y convertirlo en cadena de caracteres
	\param path ruta en la que se encuentra el archivo
	\param buffer puntero a cadena de caracteres donde se escribe el file
*/
void file_open(const char* path,char * buffer);

/*! \fn char* string_parse(const char * buffer, char * string, int ch)
	\brief Partir una cadena de caracteres hasta un salto de lìnea
	\param buffer cadena de caracteres de entrada/ salida
	\param string cadena de caracteres que indica a partir de donde se corta la linea
	\param ch ascii del primer caracter de la linea
*/
char* string_parse(const char * buffer, char * string, int ch);

/*! \fn void num_to_norm(const int num, char result [20])
	\brief A partir de un entero lo transforma en cadena de caracteres para que se vea de una forma amigable
	\param result cadena de caracteres de entrada/ salida
	\param num entero de entrada
*/
void num_to_norm(const int num, char result [20]);
#endif