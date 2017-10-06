/*! \file tools.h
    \brief Este archivo contiene herramientas de utilidad
*/

/*! \def MAX_BUFFER
    \brief Tamaño maximo del buffer donde se van a guardar los datos obtenidos en la funcion file_open
*/
#ifndef	KERNEL_INFO_H
#define	KERNEL_INFO_H

#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void save_kernel_info_2_file(FILE *f);

#endif