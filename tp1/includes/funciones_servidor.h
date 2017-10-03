/*! \file funciones_servidor.h
    \brief Este archivo contiene las funciones de lectura del archivo de datos meteorologicos
*/

#ifndef FUNCIONES_SERVIDOR_H
#define FUNCIONES_SERVIDOR_H

const char nombre_usuario[10] = "guti";
const char contrasena_usuario[10] = "belgrano";

const char prompt [50] = "guti@127.0.0.1:";

char ** split_line(char * line);

int inicializar_servidor_tcp(int sockfd, struct sockaddr_in* serv_addr, int port);
int inicializar_servidor_udp(int socket_udp, struct sockaddr_in* serv_addr, int port);

void enviar_funciones_servidor(int newsockfd, const char * funciones_servidor[]);

int eleccion_funcion(char ** buffer, const char ** funciones_servidor);

void ejecutar_funcion(int num_funcion, char ** buffer_parseado);

int validar_nombre_usuario (char ** buffer_parseado, const char * nombre_usuario, int newsockfd);

int validar_contrasena (char ** buffer_parseado, const char * contrasena, int newsockfd);

int validar_nombre_variable(char * nombre_variable);

void enviar_respuesta(int num_funcion, int sockfd);

void desconectar_servidor();

void enviar_respuesta_udp(int sock_udp, struct sockaddr_in* cli_addr, int tamano_direccion);

#endif