/*! \file get_fromProc.h
    \brief Este archivo toma y procesa los documentos de /proc para poder obtener los datos que se necesitan
*/

/*! \struct CPU
	\brief Guarda valores de interes del directorio /proc/cpuinfo
	\param model el modelo de CPU
	\param type el tipo de procesador
	\param kernel_version
*/

/*! \struct header
	\brief Guarda valores de interes para crear la cabecera del programa
	\param hostname el nombrede la maquina
	\param time_now fecha y hora actuales
*/

/*! \struct proc_stats
	\brief Guarda valores de interes del directorio /proc/stat 
	\param ctxt Cantidad de cambios de contexto. 
	\param n_proc Número de procesos creados desde el inicio del sistema. 
	\param time_idle Cantidad de tiempo de CPU utilizado para proceso idle.
	\param time_init Fecha y hora cuando el sistema fue iniciado. 
	\param time_sys Cantidad de tiempo de CPU utilizado para sistema
	\param time_user Cantidad de tiempo de CPU utilizado para usuarios

*/

/*! \struct mem_disk
	\brief Guarda valores de interes relaticvos a la memoria y el disco
	\param disk_rw Número de peticiones a disco realizadas. 
	\param mem_total Cantidad de memoria configurada en el hardware. 
	\param mem_free Cantidad de memoria disponible. 
	\param load_min Promedio de carga de 1 minuto. 
*/

/*! \fn double proc_uptime (const char* buffer)
	\brief Obtiene el valor de uptime de cadena de caracteres
	\param buffer Cadena de caracteres de entrada
	\return valor en segundos del tiempo transcurrido desde que se inicio el SO
*/

/*! \fn double proc_init_time(const char * buffer);
	\brief Obtiene la hora en segundos en que se inicio el SO
	\param buffer Cadena de caracteres de entrada
	\return valor en segundos de la hora en que se inicio el SO
*/

/*! \fn void proc_model_type(const char * buffer, struct CPU * cpu)
	\brief Imprime el modelo y tipo de CPU de cadena de caracteres
	\param buffer Cadena de caracteres de entrada
	\param cpu estructura CPU con datos de salida
*/

/*! \fn void proc_cpu_times(const char * buffer, struct proc_stats * p_stat)
	\brief Imprime el tiempo de procesador utilizado en distintos casos a partir de cadena de caracteres
	\param buffer Cadena de caracteres de entrada
	\param p_stat estructura proc_stats con datos de salida
*/

/*! \fn void proc_stat(const char * buffer, struct proc_stats * p_stat)
	\brief Imprime informacion del file /proc/stat partir de su cadena de caracteres
	\param buffer Cadena de caracteres de entrada
	\param p_stat estructura proc_stats con datos de salida
*/

/*! \fn void proc_kernel_version(const char * buffer, struct CPU * cpu)
	\brief Imprime version de kernel a partir de cadena de caracteres
	\param buffer Cadena de caracteres de entrada
	\param cpu estructura CPU con datos de salida
*/

/*! \fn void proc_header(const char * buffer, struct header * hdr)
	\brief Imprime la cebecera del programa con hostname y hora
	\param buffer Cadena de caracteres que incluya a hostname
	\param hdr estrucctura header con datos de salida
*/

/*! \fn int proc_file_sys_count(const char * buffer)
	\brief Cuenta la cantidad de file systems que soporta el SO
	\param buffer Cadena de caracteres de entrada
	\return catidad de FS que soporta el SO
*/

#ifndef	GETFROMPROC_H
#define	GETFROMPROC_H

#include "../includes/tools.h"
#include "../includes/timeTools.h"

struct CPU{
	char * model;
	char * type;
	char * kernel_version;
};


struct header{
	char * hostname;
	struct tm * time_now;
};


struct proc_stats{
	float time_idle;
	float time_sys;
	float time_user;
	char * ctxt;
	char * n_proc;
	struct tm * time_init;
};




struct mem_disk{
	int disk_rw;
	int mem_total;
	int mem_free;
	float load_min;	
};


double proc_uptime (const char* buffer); 


double proc_init_time(const char * buffer); 


void proc_model_type(const char * buffer, struct CPU * cpu);


void proc_cpu_times(const char * buffer, struct proc_stats * p_stat);


void proc_stat(const char * buffer, struct proc_stats * p_stat);


void proc_kernel_version(const char * buffer, struct CPU * cpu);


void proc_header(const char * buffer, struct header * hdr);


int proc_file_sys_count(const char * buffer);


void proc_diskstat (const char * buffer, struct mem_disk * md);
void proc_meminfo  (const char * buffer, struct mem_disk * md);
void proc_loadavg  (const char * buffer, struct mem_disk * md);

#endif