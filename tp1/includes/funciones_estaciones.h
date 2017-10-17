/*! \file funciones_estaciones.h
    \brief Este archivo contiene las funciones de lectura del archivo de datos meteorologicos
*/

#ifndef FUNCIONES_ESTACIONES_H
#define FUNCIONES_ESTACIONES_H

const char * funciones_servidor[] = {
    "Funciones del Servidor:",
    "\t listar",
    "\t precipitacion_mensual [numero_de_estacion]",
    "\t precipitacion_diaria [numero_de_estacion]",
    "\t promedio [nombre_variable]",
    "\t descargar [numero_de_estacion]",
    "\t desconectar",
    "*",
    NULL
};


/*! \fn listar()
	\brief muestra un listado de todas las estaciones que hay en la “base de datos”, y muestra de que sensores tiene datos.
*/
void listar();




/*! \fn void mensual_precipitacion(unsigned int id_estacion, float * precip_mensual)
	\brief Segun un ID pasado por parametro obtiene la estacion con ese ID y escribe en la direccion que apunta precip_mensual los datos 
	ordenados segun el orden de los meses
*/
void mensual_precipitacion(unsigned int id_estacion);

/*! \fn void diario_precipitacion(unsigned int id_estacion, float * precip_diaria)
	\brief Segun un ID pasado por parametro obtiene la estacion con ese ID y escribe en la direccion que apunta precip_diaria los datos 
	ordenados segun el orden de los dias en un mes
*/
void diario_precipitacion(unsigned int id_estacion);

/*! \fn void promedio_variable( char * variable, float * promedio)
    \brief tiene un string como parametro que indica la variable que se desea listar y un puntero al inicio de un arreglo de flotantes
    a donde comenzara la lista de promedios ordenados segun las estaciones
*/
void promedio_variable( char * variable);

void descargar ( int id_estacion );




#endif