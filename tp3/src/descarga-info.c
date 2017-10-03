#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/print_html.h"
#include "../includes/funciones_genericas.h"
#include "../includes/includes.h"
#include "../includes/variables.h"
#include "../includes/funciones_estaciones.h"
#include "../includes/lectura_archivo.h"

void print_btn(const char * btn[])
{
  for (int i = 0; btn[i] != NULL; ++i)
  {
    printf("%s", btn[i]);

  }
}

int main( int argc, char *argv[] ) {
  printf ( "%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10 );
  char* data = getenv("QUERY_STRING");
  char **parametros;
  char *id;

    const char * btn[] = {
//  "<!DOCTYPE html>",
//  "<html lang=\"en\">",
//  "<head> \n",
  "<div class=\"row\">",
  "<div class=\"col-md-6\">",
  "<a href=\"/tp3/cgi/descargar.cgi?file=descargar.txt\" class=\"btn btn-primary\">",
  "Descargar",
  "<i class=\"fa fa-download\"></i>",
  "</a>",
  "<div class=\"col-md-6\">",
  "<a href=\"/tp3/html/estaciones.html\" class=\"btn btn-default\">",
  "Atras",
  "</a>",
  "</div>",
  "</div>",
  NULL
};

  cargar_header();
  printf("<body>");
  cargar_navbar();
  cargar_archivo();




  if (data != 0)
  {
    parametros = split_line(data);
    id = parametros[1];
        descargar(atoi(id));

    struct Estacion_Meteorologica station;
    estacion_por_id ( atoi(id), &station );
    printf("<div class=\"container-fluid\">\n");
    printf("<h4>¿Seguro quieres descargar los datos de la estacion %s?</h4>\n", station.nombre);
    printf("</br>\n");
    print_btn(btn);
    printf("</div>\n");

    //num_funcion = eleccion_funcion(funcion);
    //enviar_respuesta(num_funcion);


  }
  else
  {
    printf("Error: No name provided.\n");
  }

  printf("</body>");
  printf("%s\n", "</html>");

  return 0;
}