#include "../includes/variables.h"
#include "../includes/includes.h"
#include "../includes/funciones_socket.h"



/*! \def TOKEN_BUFSIZE
    \brief Tamaño maximo del buffer para palabras de consola
*/
#define TOKEN_BUFSIZE 64
/*! \def TOKEN_DELIM
    \brief Delimitadores de la linea de comandos
*/
#define TOKEN_DELIM " \t\r\n\a@:"

#define N_PUERTO 6020

char ** split_line(char * line){
  int bufsize = TOKEN_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;
  char * rest;
  //strcpy(rest,line);

  token = strtok_r(line,TOKEN_DELIM,&rest);

  while (token != NULL) {      //Mientras haya tokens
    tokens[position] = token;     //Los guardo en un arreglo
    position = position + 1;

    if (position >= bufsize) { //Si el arreglo excede al tamaño prestablecido, agrando el buffer y sigo guardando
      bufsize += TOKEN_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        free(tokens_backup);
        fprintf(stderr, "Baash: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok_r(NULL, TOKEN_DELIM,&rest);
  }
  //free(rest);
  tokens[position] = NULL;
  return tokens;
}



int inicializar_servidor_tcp(int sockfd, struct sockaddr_in* serv_addr, int port)
{
  //printf("INICIANDO TCP\n");
  sockfd = socket( AF_INET, SOCK_STREAM, 0);
  if ( sockfd < 0 ) { 
    perror( " apertura de socket ");
    exit( 1 );
  }

  memset( (char *) serv_addr, 0, sizeof(*serv_addr) );

  serv_addr->sin_family = AF_INET;
  serv_addr->sin_addr.s_addr = INADDR_ANY;
  serv_addr->sin_port = htons( port );

  if ( bind(sockfd, ( struct sockaddr *) serv_addr, sizeof( *serv_addr ) ) < 0 ) {
    perror( "ligadura" );
    exit( 1 );
  }

  printf( "Proceso: %d - socket TCP disponible: %d\n", getpid(), ntohs(serv_addr->sin_port) );

  listen( sockfd, 5 );
  return sockfd;

}

int inicializar_servidor_udp(int socket_udp, struct sockaddr_in* serv_addr, int port)
{

  socket_udp = socket( AF_INET, SOCK_DGRAM, 0 );
  if (socket_udp < 0) { 
    perror("ERROR en apertura de socket");
    exit( 1 );
  }

  memset( serv_addr, 0, sizeof(*serv_addr) );

  serv_addr->sin_family = AF_INET;
  serv_addr->sin_addr.s_addr = INADDR_ANY;
  serv_addr->sin_port = htons( port );
  memset( (serv_addr->sin_zero), '\0', 8 );

  if( bind( socket_udp, (struct sockaddr *) serv_addr, sizeof(*serv_addr) ) < 0 ) {
    perror( "ERROR en binding" );
    exit( 1 );
  }

  printf( "Socket (UDP) disponible : %d\n", ntohs(serv_addr->sin_port) );

  return socket_udp;

}
void enviar_funciones_servidor(int newsockfd, const char * funciones_servidor[])
{
  int socketResult;
  socketResult = escribir_socket(newsockfd, funciones_servidor[0]);
  if (socketResult == -1) printf("Error en transferencia en el socket\n");
  socketResult = escribir_socket(newsockfd, funciones_servidor[1]);
  if (socketResult == -1) printf("Error en transferencia en el socket\n");
  socketResult = escribir_socket(newsockfd, funciones_servidor[2]);
  if (socketResult == -1) printf("Error en transferencia en el socket\n");
  socketResult = escribir_socket(newsockfd, funciones_servidor[3]);
  if (socketResult == -1) printf("Error en transferencia en el socket\n");
  socketResult = escribir_socket(newsockfd, funciones_servidor[4]);
  if (socketResult == -1) printf("Error en transferencia en el socket\n");
  socketResult = escribir_socket(newsockfd, funciones_servidor[5]);
  if (socketResult == -1) printf("Error en transferencia en el socket\n");
  socketResult = escribir_socket(newsockfd, funciones_servidor[6]);
  if (socketResult == -1) printf("Error en transferencia en el socket\n");

  return;
}

int eleccion_funcion(char ** buffer_parseado, const char ** funciones_servidor)
{
  if (!strcmp(buffer_parseado[0],"listar")) return 1;
  else if (!strcmp(buffer_parseado[0],"precipitacion_mensual")) return 2;
  else if (!strcmp(buffer_parseado[0],"precipitacion_diaria")) return 3;
  else if (!strcmp(buffer_parseado[0],"promedio")) return 4;
  else if (!strcmp(buffer_parseado[0],"descargar")) return 5;
  else if (!strcmp(buffer_parseado[0],"desconectar")) return 6;
  else return 0;
}

void desconectar_servidor()
{
  printf( "PROCESO %d. Como recibí 'desconectar', termino la ejecución.\n\n", getpid() );
  exit(EXIT_SUCCESS);

}

int validar_nombre_usuario (char ** buffer_parseado, const char * nombre_usuario, int newsockfd)
{
  if (!strcmp(buffer_parseado[0],nombre_usuario))
  {
    escribir_socket(newsockfd,"correcto");
    return 0;
  } else {
    escribir_socket(newsockfd,"incorrecto");
    return 1;
  }
  
}

int validar_contrasena (char ** buffer_parseado, const char * contrasena, int newsockfd)
{

  if (!strcmp(buffer_parseado[0],contrasena))
  {
    escribir_socket(newsockfd,"correcto");
    return 0;
  } else {
    escribir_socket(newsockfd,"incorrecto");
    return 1;
  }
}

int validar_nombre_variable(char * nombre_variable)
{
  if ( strcmp ( nombre_variable, "Temperatura" ) == 0 ) { return 1; }
  else if ( strcmp ( nombre_variable, "Humedad" ) == 0 ) { return 1; }
  else if ( strcmp ( nombre_variable, "Punto de rocio" ) == 0 ) { return 1;}
  else if ( strcmp ( nombre_variable, "Precipitacion" ) == 0 ) { return 1; }
  else if ( strcmp ( nombre_variable, "Velocidad del viento" ) == 0 ) { return 1; }
  else if ( strcmp ( nombre_variable, "Rafaga Maxima" ) == 0 ) { return 1; }
  else if ( strcmp ( nombre_variable, "Presion" ) == 0 ) { return 1; }
  else if ( strcmp ( nombre_variable, "Radiacion Solar" ) == 0 ) { return 1; }
  else if ( strcmp ( nombre_variable, "Temperatura del suelo 1") == 0 ) { return 1;}
  else { return 0;} 
}

void enviar_respuesta(int num_funcion, int sockfd)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;


  switch(num_funcion)
  {
    case 1:
    fp = fopen(A_LISTAR, "r");
    break;
    case 2:
    fp = fopen(A_MENSUAL_PRECIP, "r");
    break;
    case 3:
    fp = fopen(A_DIARIO_PRECIP, "r");
    break;
    case 4:
    fp = fopen(A_PROM_VAR, "r");
    break;
  }

  while((nread = getline(&line, &len, fp))!= -1)
  {
    escribir_socket(sockfd,line);
  }

  escribir_socket(sockfd,"***");

  return;

}

