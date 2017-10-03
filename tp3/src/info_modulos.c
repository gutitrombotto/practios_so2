#include <stdio.h>
#include <string.h>
#include "../includes/print_html.h"


int main( int argc, char *argv[] ) {

	printf ( "%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10 );

	cargar_header();
	printf("<body>");
	cargar_navbar();
	
	printf("ACA VA LA INFO DE LOS MODULOS\n\n");
	printf("</body>");
	printf("%s\n", "</html>");
	return 0;
}
