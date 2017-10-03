/*! \file funciones_socket.h
    \brief Este archivo contiene las funciones de lectura del archivo de datos meteorologicos
*/

#ifndef FUNCIONES_SOCKET_H
#define FUNCIONES_SOCKET_H

#include <netdb.h>


int escribir_socket(int sockfd, const char* buffer);

int leer_socket(int sockfd,char* buffer);


#endif