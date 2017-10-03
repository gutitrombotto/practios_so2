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

#define TAM 256
#define A_DESCARGAR "./descargar.txt"

char ** split_line(char * line){
	int bufsize = TOKEN_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_backup;
	char * rest;
	//strcpy(rest,line);

	token = strtok_r(line,TOKEN_DELIM,&rest);

	while (token != NULL) {      //Mientras haya tokens
		tokens[position] = token;     //Los guardo en un arreglo
		position++;

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

int test_linea_parseada(char ** linea_parseada, char ** datos_coneccion)
{
	if(strcmp(linea_parseada[0], datos_coneccion[0])) return 1;
	if(strcmp(linea_parseada[1], datos_coneccion[1])) return 1;
	if(strcmp(linea_parseada[2], datos_coneccion[2])) return 1;
	if(strcmp(linea_parseada[3], datos_coneccion[3])) return 1;
	else return 0;
}

void leer_funciones_servidor(int sockfd,char* buffer)
{
	leer_socket(sockfd, buffer);
	printf("%s\n", buffer);
	leer_socket(sockfd, buffer);
	printf("%s\n", buffer);
	leer_socket(sockfd, buffer);
	printf("%s\n", buffer);
	leer_socket(sockfd, buffer);
	printf("%s\n", buffer);
	leer_socket(sockfd, buffer);
	printf("%s\n", buffer);
	leer_socket(sockfd, buffer);
	printf("%s\n", buffer);
	leer_socket(sockfd, buffer);
	printf("%s\n", buffer);

	return;
}

