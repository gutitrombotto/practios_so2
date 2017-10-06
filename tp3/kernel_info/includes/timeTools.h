/*! \file timeTools.h
    \brief Este archivo contiene herramientas relaconadas con el manejo de la libreria time
*/

#ifndef	TIMETOOLS_H
#define	TIMETOOLS_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/*! \fn double get_sec(void);
	\brief Devuelve el numero en segundos correspondiente al dia y hora actuales
	\return Dia del mes y hora expresados en sgundos
*/
double get_sec(void);
/*! \fn struct tm * sec_to_Time(double sec);
	\brief A partir de un double en segundos devuelve un objeto tiempo para que pueda ser impreso con mas facilidad
	\param sec Segundos a convertir en formato tiempo
	\return Estructura time, organzada de manera tal que sea compatible con sec_to_Time()
*/
struct tm * sec_to_Time(double sec);

/*! \fn void print_clock(struct tm * hora, char *txt, int index)
	\briefA partir de una estructura de tiempo, la imprime de un modo distinto segun index
	Agrega titulo 
	\param hora Estructura time
	\param txt 	Titulo al inicio de output
	\param index Indice para indicar el formato de impresion
		0-- para imprimir tiempo en formato ddD hh:mm:ss
		1-- para imprimir una fecha dd/MM/AA hh:mm:ss
*/
void print_clock(struct tm * hora, char *txt, int index, FILE *f);

#endif