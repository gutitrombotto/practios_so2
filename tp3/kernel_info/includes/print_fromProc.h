/*! \file print_fromProc.h
    \brief Utiliza la funcion file_open() para crear buffers y enviarlos las funciones 
 	de get_fromProc.h correspondientes.
	En algunos casos toma los datos de get_fromProc y los modifica para que se 
 	vean mejor.
*/

/*! \def MAX_BUFFER
    \brief Tamaño maximo del buffer donde se van a guardar los datos obtenidos en la funcion file_open
*/
#ifndef	PRINTFROMPROC_H
#define	PRINTFROMPROC_H

#include "../includes/get_fromProc.h"

#define MAX_BUFFER 5000
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


void print_uptime (FILE *f); 
void print_model_type(FILE *f);
void print_initTime();
void print_stat();
void print_kernel_version(FILE *f);
void print_header(FILE *f);		
void print_file_sys_count();
void print_diskstat ();
void print_meminfo  (FILE *f);
void print_loadavg  ();


#endif