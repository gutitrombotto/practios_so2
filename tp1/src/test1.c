#include "../includes/includes.h"
#include "../includes/variables.h"
#include "../includes/lectura_archivo.h"
#include "../includes/funciones_estaciones.h"
#include "../includes/funciones_servidor.h"
#include "../includes/funciones_socket.h"
#include <arpa/inet.h>

int main ( int argc, char* argv[] )
{
	int sockfd = 0, socket_udp = 0, n;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    int socketResult, validar_usuario=1, validar_pw=1, envio_func=1, tamano_direccion;
    char buffer [TAM];
    char ** buffer_parseado;
    int puerto = 6020;

    cargar_archivo();

    sockfd = inicializar_servidor_tcp(sockfd, &serv_addr, puerto);
    clilen = sizeof( cli_addr );

    socket_udp= inicializar_servidor_udp(socket_udp, &serv_addr, puerto);
    tamano_direccion = sizeof( struct sockaddr );
    socklen_t slen = sizeof( struct sockaddr );

    //inicializar_servidor_tcp(&sockfd, &clilen, &serv_addr, &cli_addr);


    //sock_udp = socket (AF_INET, SOCK_DGRAM, 0);
    while( 1 ) {
        int newsockfd, pid;
        newsockfd = accept ( sockfd, ( struct sockaddr* ) &cli_addr,
           ( socklen_t* ) &clilen );

        if ( newsockfd < 0 ) {
            perror( "accept" );
            exit( 1 );
        }

        pid = fork(); 
        if ( pid < 0 ) {
            perror( "fork" );
            exit( 1 );
        }
        if ( pid == 0 ) {
            /*!< Proceso hijo, gestiona la conexion con un solo cliente */
            close( sockfd );

            /*!< Bucle de validar_usuario. Leo el usuario y contraseña proporcionados
            y lo valido.*/
            while ( validar_usuario ) {
                memset( buffer, 0, TAM );
                socketResult = leer_socket(newsockfd,buffer);
                if (socketResult == -1) printf("Error en transferencia en el socket\n");

                printf( "PROCESO %d. ", getpid() );
                printf("Recibí: %*.*s\n", socketResult, socketResult, buffer);

                buffer_parseado = split_line(buffer);
                validar_usuario = validar_nombre_usuario(buffer_parseado, nombre_usuario, newsockfd);
                
            }

            while (validar_pw)
            {
                memset( buffer, 0, TAM );
                socketResult = leer_socket(newsockfd,buffer);
                if (socketResult == -1) printf("Error en transferencia en el socket\n");


                printf( "PROCESO %d. ", getpid() );
                printf("Recibí: %*.*s\n", socketResult, socketResult, buffer);

                buffer_parseado = split_line(buffer);
                validar_pw = validar_contrasena(buffer_parseado, contrasena_usuario, newsockfd);

            }

            socketResult = escribir_socket(newsockfd,prompt);
            if (socketResult == -1) printf("Error en transferencia en el socket\n");

            

            while(1) 
            {
                while (envio_func)
                {
                    enviar_funciones_servidor(newsockfd, funciones_servidor);
                    
                    memset( buffer, 0, TAM );
                    socketResult = leer_socket(newsockfd,buffer);
                    if (socketResult == -1) printf("Error en transferencia en el socket\n");


                    printf( "PROCESO %d. ", getpid() );
                    printf("Recibí: %*.*s\n", socketResult, socketResult, buffer);

                    buffer_parseado = split_line(buffer);

                    int num_funcion = eleccion_funcion(buffer_parseado, funciones_servidor);

                    printf("%d\n", num_funcion);
                    //ejecutar_funcion(num_funcion, buffer_parseado);
                    switch(num_funcion)
                    {
                        case 0:
                        printf("%s\n", "Error en la seleccion del funcion");
                        socketResult = escribir_socket(newsockfd,"Error en la seleccion del funcion \n");
                        if (socketResult == -1) printf("Error en transferencia en el socket\n");

                        escribir_socket(newsockfd,"***");
                        break;

                        case 1:
                        printf("%s\n", "Ejecutando Listar");
                        listar();
                        enviar_respuesta(num_funcion, newsockfd);
                        break;

                        case 2:
                        printf("%s\n", "Ejecutando Precipitacion Mensual");
                        if (existe_estacion ( atoi (buffer_parseado[1]) ) != 0 )
                        {
                            mensual_precipitacion(atoi(buffer_parseado[1]));
                            enviar_respuesta(num_funcion, newsockfd);
                        } else { 
                            printf("%s\n", "No Existe Estacion con ese numero...");
                            socketResult = escribir_socket(newsockfd,"No Existe Estacion con ese numero... \n");
                            if (socketResult == -1) printf("Error en transferencia en el socket\n");

                            escribir_socket(newsockfd,"***");
                        }
                        break;

                        case 3:
                        printf("%s\n", "Ejecutando Precipitacion Diaria");
                        if (existe_estacion ( atoi (buffer_parseado[1]) ) != 0 )
                        {
                            diario_precipitacion(atoi(buffer_parseado[1]));
                            enviar_respuesta(num_funcion, newsockfd);
                        } else {
                            printf("%s\n", "No Existe Estacion con ese numero...");
                            socketResult = escribir_socket(newsockfd,"No Existe Estacion con ese numero... \n");
                            if (socketResult == -1) printf("Error en transferencia en el socket\n");

                            escribir_socket(newsockfd,"***");

                        }
                        break;

                        case 4:
                        printf("%s\n", "Ejecutando Promedio de Variable");
                        if (validar_nombre_variable(buffer_parseado[1]))
                        {
                            promedio_variable(buffer_parseado[1]);
                            enviar_respuesta(num_funcion, newsockfd);
                        } else {
                            printf("%s\n", "Nombre de variable no valido...");
                            socketResult = escribir_socket(newsockfd,"Nombre de variable no valido... \n");
                            if (socketResult == -1) printf("Error en transferencia en el socket\n");

                            escribir_socket(newsockfd,"***");
                        }
                        
                        break;

                        case 5:
                        if (existe_estacion ( atoi (buffer_parseado[1]) ) != 0 )
                        {
                            printf("%s\n", "Ejecutando Descargar info");
                            descargar(atoi(buffer_parseado[1]));
                            socketResult = escribir_socket(newsockfd,"descargo_udp");
                            if (socketResult == -1) printf("Error en transferencia en el socket\n");

                            //tamano_udp = sizeof ( serv_addr );
                            //socklen_t slen = sizeof serv_addr;


                            /* UDP */
                            memset( buffer, 0, TAM );
                            n = recvfrom( socket_udp, buffer, TAM-1, 0, (struct sockaddr *)&serv_addr, &slen );
                            if ( n < 0 ) {
                                perror( "lectura de socket" );
                                exit( 1 );
                            }
                            printf( "Recibí de UDP: %s", buffer );

                            char* line = NULL;

                            size_t bufsize = 0;
                            //ssize_t nread;
                            //int n;


                            FILE *fp = fopen ( A_DESCARGAR, "r" );

                            if ( fp == NULL )
                            {
                                printf ( "Error opening file!\n" );
                                exit ( 1 );
                            }
                            else
                            {
                                int n;
                                ssize_t nread;
                                while ( (nread = getline ( &line, &bufsize, fp ) ) != -1 ) 
                                {
                                    printf("Envioando: %s\n", line);
                                    n = sendto ( socket_udp, ( void* ) line, nread, MSG_CONFIRM, ( struct sockaddr* ) &serv_addr, tamano_direccion );
                                    if ( n < 0 ) 
                                    {
                                        perror ( "Escritura en socket UDP " );
                                        exit ( 1 );
                                    }
                                }

                                n = sendto ( socket_udp, "FIN_UDP", strlen ( "FIN_UDP" ), MSG_CONFIRM, ( struct sockaddr* ) &serv_addr, tamano_direccion );
                                printf("Envie FIN_UDP: \n");

                                if ( n < 0 ) 
                                {
                                  perror ( "Escritura en socket UDP" );
                                  exit ( 1 );
                              }
                          }

                            //enviar_respuesta_udp(socket_udp,&serv_addr, tamano_direccion);


                            /*n = sendto( socket_udp, (void *)"Obtuve su mensaje", 18, 0, (struct sockaddr *)&serv_addr, tamano_direccion  );
                            if ( n < 0 ) {
                                perror( "escritura en socket" );
                                exit( 1 );
                            }
                            memset( buffer, 0, TAM );*/

                            /* FIN UDP */                         

                      } else { 
                        printf("%s\n", "No Existe Estacion con ese numero...");
                        socketResult = escribir_socket(newsockfd,"No Existe Estacion con ese numero... \n");
                        if (socketResult == -1) printf("Error en transferencia en el socket\n");

                        escribir_socket(newsockfd,"***");
                    }

                    break;
                    case 6:

                    printf("%s\n", "Ejecutando Desconectando");
                    socketResult = escribir_socket(newsockfd,"Desconectando");
                    if (socketResult == -1) printf("Error en transferencia en el socket\n");

                    escribir_socket(newsockfd,"***");
                    desconectar_servidor();
                    break;
                }

            }

            while(1)
            {
                printf("%s\n", "ESTOY ACA");
                memset( buffer, 0, TAM );
                socketResult = leer_socket(newsockfd,buffer);
                if (socketResult == -1) printf("Error en transferencia en el socket\n");

                printf("%s\n", "YA LEI");
                printf("Recibí: %*.*s\n", socketResult, socketResult, buffer);

            }


        }

    }
    else {
        printf( "SERVIDOR: Nuevo cliente, que atiende el proceso hijo: %d\n", pid );
        close( newsockfd );
    }
}

exit(EXIT_SUCCESS);
}
