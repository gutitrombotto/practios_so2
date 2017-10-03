#include <stdio.h>
#include <string.h>
#include "../includes/print_html.h"
#include "../includes/funciones_genericas.h"

#include <stdlib.h>


int main( int argc, char *argv[] ) {
printf ( "%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10 );
char* data = getenv("QUERY_STRING");
char **parametros;
char *id;

cargar_header();
  printf("<body>");
  cargar_navbar();
    printf("ACA VA PRECIPITACION DIARIA\n\n");

  if (data != 0)
  {
      parametros = split_line(data);
      id = parametros[1];
  }
  else
  {
    printf("Error: No name provided.\n");
  }

  printf("Parametros: %s - %s\n", parametros[0], parametros[1]);

  printf("</body>");
  printf("%s\n", "</html>");

  return 0;
}