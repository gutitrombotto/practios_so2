#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../includes/print_html.h"
#include "../includes/funciones_genericas.h"


int main( int argc, char *argv[] ) {
	system("./ksamp");

char * nombre_archivo = "./info-kernel.txt";
printf ( "%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10 );

cargar_header();
	printf("<body>");
	cargar_navbar();
	printf("<div class=\"container-fluid\">");
	printf("<div class=\"row\">");
	printf("<div class=\"col-md-10 col-md-offset-1\">");

	print_file(nombre_archivo);
		printf("</div>");
	printf("</div>");
	printf("</div>");

  //printf("ACA VA LA INFO DEL SISTEMA\n\n");


	printf("</body>");
	printf("%s\n", "</html>");

  return 0;
}
