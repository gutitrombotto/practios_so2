/*! \file funciones_cliente.h
    \brief Este archivo contiene las funciones de lectura del archivo de datos meteorologicos
*/

#ifndef FUNCIONES_CLIENTE_H
#define FUNCIONES_CLIENTE_H


#include <arpa/inet.h>

char ** split_line(char * line);

int test_linea_parseada(char ** linea_parseada, char ** datos_coneccion);

void leer_funciones_servidor(int sockfd,char* buffer);


void recibir_descarga_udp(int sock_udp, struct sockaddr_in serv_addr, int tamano_direccion);


#endif