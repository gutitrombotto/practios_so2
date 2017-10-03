#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../includes/print_html.h"
#include "../includes/funciones_genericas.h"
#include "../includes/includes.h"
#include "../includes/variables.h"
#include "../includes/funciones_estaciones.h"
#include "../includes/lectura_archivo.h"


int main( int argc, char *argv[] ) {
printf ( "%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10 );
char* data = getenv("QUERY_STRING");
char *funcion = "diario_precip";
char **parametros;
char *id;
int num_funcion;

cargar_header();

	printf("<body>");
	cargar_navbar();
  cargar_archivo();
 /* printf("</br>");
	  printf("ACA VA PRECIPITACION DIARIA\n\n");
      printf("</br>");*/



  if (data != 0)
  {
      parametros = split_line(data);
      id = parametros[1];
      diario_precipitacion(atoi(id));

      num_funcion = eleccion_funcion(funcion);
      enviar_respuesta(num_funcion);
  }
  else
  {
    printf("Error: No name provided.\n");
  }

  //printf("Parametros: %s - %s\n", parametros[0], parametros[1]);

	printf("</body>");
	printf("%s\n", "</html>");

  return 0;
}