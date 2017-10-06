
#include "../includes/variables.h"
#include "../includes/includes.h"
/*! \def TOKEN_DELIM
    \brief Delimitadores de la linea de comandos
*/
#define TOKEN_DELIM "= "

/*! \def TOKEN_BUFSIZE
    \brief Tamaño maximo del buffer para palabras de consola
*/
#define TOKEN_BUFSIZE 64

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

void enviar_respuesta(int num_funcion)
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

  if ( fp == NULL )
  {
    printf ( "Error opening file on GF!\n" );
    exit ( 1 );
  }
  while((nread = getline(&line, &len, fp))!= -1)
  {
  	printf("%s\n", line);
  }

  return;

}

int eleccion_funcion(char * funcion_elegida)
{
  if (!strcmp(funcion_elegida,"listar")) return 1;
  else if (!strcmp(funcion_elegida,"mensual_precip")) return 2;
  else if (!strcmp(funcion_elegida,"diario_precip")) return 3;
  else if (!strcmp(funcion_elegida,"promedio")) return 4;
  else if (!strcmp(funcion_elegida,"descargar")) return 5;
  else if (!strcmp(funcion_elegida,"desconectar")) return 6;
  else return 0;
}


void print_file(char *nombre_archivo)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  fp = fopen(nombre_archivo, "r");



  if ( fp == NULL )
  {
    printf ( "Error opening file on GF!\n" );
    exit ( 1 );
  }
  while((nread = getline(&line, &len, fp))!= -1)
  {
    printf("%s\n", line);
  }

  return;

}