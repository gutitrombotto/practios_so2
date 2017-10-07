#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../includes/print_html.h"
#include "../includes/funciones_genericas.h"

const char * formulario[] = {
  "  <form action=\"/tp3/cgi/subir_archivo.cgi\" method=\"post\" enctype=\"multipart/form-data\">",
  "<h3> Elige el archivo del modulo </h3>",
  "</br>",
  "<input type=\"file\" name=\"archivo\" />",
  "</br>",
  "<input type=\"submit\" name=\"Submit\" value=\"Subir archivo\" class=\"btn btn-primary\"/>"
  " </form>",
  NULL
};

void print_cte(const char * to_print[])
{
  for (int i = 0; to_print[i] != NULL; ++i)
  {
    printf("%s", to_print[i]);

  }

  return;
}
int main( int argc, char *argv[] ) {
  printf ( "%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10 );

  cargar_header();


  printf("<body>");
  cargar_navbar();
  printf("%s", "<div class=\"container-fluid\">");
  printf("%s", "<div class=\"row\">");
  printf("%s", "<div class=\"col-md-8 col-md-offset-2\">");

  print_cte(formulario);

  printf("</div>");
  printf("</div>");
  printf("</div>");




  printf("</body>");
  printf("%s\n", "</html>");

  return 0;
}