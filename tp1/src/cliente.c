#include "../includes/includes.h"
#include "../includes/funciones_socket.h"
#include "../includes/funciones_cliente.h"

#define TAM 512
int main ( int argc, char* argv[] )
{
	int sockfd, puerto, n, socket_udp;
	struct sockaddr_in serv_addr;
	struct hostent* server;
	int terminar = 0, status = 1, validar_usuario=1, validar_pw=1,tamano_direccion;
	char* line = NULL;
	size_t bufsize = 0; // have getline allocate a buffer for us
	ssize_t nread;
	char buffer [TAM];
	char prompt [50];
	char ** linea_parseada;
	char * datos_coneccion [] = { "connect", "guti", "127.0.0.1", "6020", NULL};



	while( status )
	{
		printf("%s\n", "Escriba: connect usuario@direccion_ip:puerto");
		nread = getline ( &line, &bufsize, stdin );
		if (nread == -1) printf("Error en la Lectura de la terminal\n");
		linea_parseada = split_line(line);

		if (test_linea_parseada(linea_parseada, datos_coneccion))
		{
			printf("%s\n", "Algo esta mal al conectarse con el servidor...");
			status = 1;
		}
		else {
			printf("%s\n", "Listo para conectarse con el servidor...");
			status = 0;
		}
	}

	puerto = atoi(linea_parseada[3]);
	//puerto = atoi("6020");

	/*SOCKET TCP */
	sockfd = socket ( AF_INET, SOCK_STREAM, 0 );

	if ( sockfd < 0 )
	{
		perror ( "ERROR apertura de socket" );
		exit ( EXIT_FAILURE );
	}
	server = gethostbyname( linea_parseada[2] );
	//server = getaddrinfo( linea_parseada[2] );
	
	//server = gethostbyname( "127.0.0.1" );
	if (server == NULL) {
		fprintf( stderr,"Error, no existe el host\n");
		exit ( EXIT_FAILURE );
	}
	printf("Direccion del servidor: %s\n", server->h_name);

	memset( (char *) &serv_addr, '0', sizeof(serv_addr) );
	serv_addr.sin_family = AF_INET;
	//bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length );
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

		// serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons( puerto );

	/*FIN SOCKET TCP */


	/* SOCKET UDP*/
	//printf("INCIALIZANDO UDP\n");
	socket_udp = socket( AF_INET, SOCK_DGRAM, 0 );
	if (socket_udp < 0)
	{
		perror( "apertura de socket" );
		exit( 1 );
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons( puerto );
	serv_addr.sin_addr = *( (struct in_addr *)server->h_addr );
	memset( &(serv_addr.sin_zero), '\0', 8 );

	tamano_direccion = sizeof( serv_addr );
	socklen_t slen = sizeof( serv_addr );

	printf( "Conectado al socket: %d del servidor\n", ntohs(serv_addr.sin_port) );

	/*FIN SOCKET UDP */


	if ( connect( sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr ) ) < 0 ) {
		perror( "Conexion Fallida" );
		exit ( EXIT_FAILURE );
	} else { printf("%s\n", " ---- Conectado con el Servidor ----");}

	while (validar_usuario)
	{
		escribir_socket(sockfd,linea_parseada[1]);
		//escribir_socket(sockfd,"hola w8");
		leer_socket(sockfd, buffer);
		if (!strcmp(buffer,"correcto"))
		{
			printf("%s\n", "Usuario Validado...");
			validar_usuario = 0;
		} else {
			printf("%s\n", "Usuario incorrecto...");
			printf("%s\n", "El programa ha Terminado.");
			validar_usuario = 1;
			exit(EXIT_FAILURE);
		}
	}

	while(validar_pw)
	{
		printf("%s\n", "Coloque su contraseña");
		nread = getline ( &line, &bufsize, stdin );
		if (nread == -1) printf("Error en la Lectura de la terminal\n");


		escribir_socket(sockfd,line);
		leer_socket(sockfd, buffer);

		if (!strcmp(buffer,"correcto"))
		{
			printf("%s\n", "Contraseña Correcta...");
			validar_pw = 0;
		} else {
			printf("%s\n", "Contraseña incorrecto...");
			validar_pw = 1;
		}
	}

	leer_socket(sockfd, buffer);
	strncpy(prompt, buffer, 50);

	//printf("%s\n", "Elija alguna de las opciones del servidor");

	
	while(1)
	{
		printf("%s\n", "En eleccion_funcion");
		if (terminar)
		{
			printf("Cerrando Cliente...\n");
			exit(EXIT_SUCCESS);
		}
			//printf("%s\n", "Elija alguna de las opciones...");
		leer_funciones_servidor(sockfd,buffer);
			//nread = getline ( &line, &bufsize, stdin );
		printf("%s", prompt);

		nread = getline ( &line, &bufsize, stdin );
		if (nread == -1) printf("Error en la Lectura de la terminal\n");



		escribir_socket(sockfd,line);		

		while(strcmp(buffer,"***") != 0)
		{
			leer_socket(sockfd, buffer);
			if (!strcmp(buffer,"***")) break;
			if (!strcmp(buffer, "descargo_udp"))
			{
				printf("%s\n", "Estoy en descargo udp");
					//tamano_direccion = sizeof ( serv_addr );
					//socklen_t slen = sizeof serv_addr;
				printf( "Iniciando transmision..." );
				memset( buffer, 0, TAM );
				strcpy ( buffer, ( const char * ) "dale" );

				//fgets( buffer, TAM, stdin );

				n = sendto( socket_udp, (void *)buffer, TAM, 0, (struct sockaddr *)&serv_addr, tamano_direccion );
				if ( n < 0 ) {
					perror( "Escritura en socket" );
					exit( 1 );
				}


				memset( buffer, 0, sizeof( buffer ) );
					/*n = recvfrom( socket_udp, (void *)buffer, TAM, 0, (struct sockaddr *)&serv_addr, &slen );
					if ( n < 0 ) {
						perror( "Lectura de socket" );
						exit( 1 );
					}*/

				FILE *fp = fopen ( "descargar.txt", "w" );

				if ( fp == NULL )
				{
					printf ( "Error opening file!\n" );
					exit ( 1 );
				}

				while ( strncmp ( buffer, "FIN_UDP", strlen ( "FIN_UDP" )) != 0 )
				{
					n = recvfrom( socket_udp, (void *)buffer, TAM, MSG_WAITALL, (struct sockaddr *)&serv_addr, &slen );
					if ( n < 0 ) {
						perror( "Lectura de socket" );
						exit( 1 );
					}
					if (n == 0)
					{
						printf(" Se perdio un paquete \n" );
					}
					printf( "Respuesta: %s\n", buffer );
					fprintf(fp, "%s", buffer);
					if (!strncmp ( buffer, "FIN_UDP", strlen ( "FIN_UDP" ))) break;

					memset( buffer, 0, sizeof( buffer ) );
				}
				fclose ( fp );

				break;
					/* FIN MSG UDP*/

   					/*printf("%s\n", "Dercargando Archivo... ");
					tamano_direccion = sizeof ( serv_addr );
					recibir_descarga_udp(sock_udp, serv_addr, tamano_direccion);*/
			} else if (!strcmp(buffer, "Desconectando")){
				terminar = 1;
			} else {
				printf("%s\n", buffer);
			}
		}


	}
	
	exit(EXIT_SUCCESS);
}
