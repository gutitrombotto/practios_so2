#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/print_html.h"
#include "../includes/funciones_genericas.h"
#include "../includes/header.h"


#define TAM 200

void cargar_header_to_file(FILE *f)
{
	for (int i = 0; head[i] != NULL; ++i)
	{
		fprintf(f,"%s", head[i]);

	}
}

void cargar_navbar_to_file(FILE *f)
{
	for (int i = 0; nav_bar[i] != NULL; ++i)
	{
		fprintf(f,"%s", nav_bar[i]);

	}
}

const char * inicio_table[] = {
  "  <div class=\"panel panel-primary\">",
  "<div class=\"panel-heading\">",
  "Modulos del Kernel",
  "</div>",
  "<div class=\"panel-body\">",
  " <table class=\"table\">",
  "<thead>",
  "<tr>",
  "<th> Nombre Modulo </th>",
  "<th> Tamano </th>",
   "<th> Usado por </th>",
  "</tr>",
  "</thead>",
  "<tbody>",
  NULL
};

const char * end_of_table[] = {
  "</tbody>",
  "</table>",
  "</div>",
  "</div>",
  NULL
};
void print_cte_to_file(const char * to_print[], FILE *f)
{
  for (int i = 0; to_print[i] != NULL; ++i)
  {
    fprintf(f,"%s", to_print[i]);

  }

  return;
}

void print_datos_to_file(FILE *f, char mod_nombre[], char mod_size[], char mod_usado_por[], char mod_usado_por2[])
{

	fprintf(f, "<tr>\n");
	fprintf(f, "<td> %s </td> \n",  mod_nombre);
	fprintf(f, "<td> %s </td> \n", mod_size);
	fprintf(f, "<td> %s ",  mod_usado_por);
	if (strcmp(mod_usado_por2,"-1") != 0) fprintf(f,"%s </td> \n", mod_usado_por2);
	else fprintf(f,"%s", "</td>\n");
	fprintf(f,"%s", "</tr>\n");


  return;
}
int main( int argc, char *argv[] ) {
	printf ( "%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1", 13, 10 );
	system("lsmod >> ../archivos/lista_modulos.txt");
	FILE *fp;
	FILE *f;
	char *line = NULL;
	char mod_nombre [TAM];
	char mod_size[TAM];
	char mod_usado_por[TAM];
	char mod_usado_por2[TAM];

	size_t len = 0;
	ssize_t nread;
	char **splited_line;
	int lineas_innecesarias = 1;


	fp = fopen("../archivos/lista_modulos.txt", "r+");
	if ( fp == NULL )
	{
		printf ( "Error opening file on Info Modulos!\n" );
		exit ( 1 );
	}
	f = fopen("../archivos/lista_modulos_html.txt", "w+");
	if ( f == NULL )
	{
		printf ( "Error opening file on Info Modulos!\n" );
		exit ( 1 );
	}
	while (getline(&line, &len, fp))
	{
		if (!lineas_innecesarias)    break;
		lineas_innecesarias --;
	}


	cargar_header_to_file(f);
	fprintf(f,"%s","<body>");
	cargar_navbar_to_file(f);
	fprintf(f, "%s", "<div class=\"container-fluid\">");
	fprintf(f, "%s", "<div class=\"row\">");
	fprintf(f, "%s", "<div class=\"col-md-10 col-md-offset-1\">");
	print_cte_to_file(inicio_table,f);

	while((nread = getline(&line, &len, fp))!= -1)
	{
		//printf("%s\n", line);
		splited_line = split_line(line);
		strcpy ( mod_nombre, ( const char * ) splited_line[0] );
		strcpy ( mod_size, ( const char * ) splited_line[1] );
		//itoa(a,buffer,2)
		strcpy ( mod_usado_por, ( const char * ) splited_line[2] );
		if (splited_line[3] != NULL)  strcpy ( mod_usado_por2, ( const char * ) splited_line[3] );
		else strcpy ( mod_usado_por2, "-1" );

		/*mod_nombre = splited_line[0];
		mod_size = splited_line[1];
		mod_usado_por = splited_line[2];*/
		print_datos_to_file(f, mod_nombre, mod_size, mod_usado_por,mod_usado_por2);
		/*printf("Nombre modulo: %s\n", mod_nombre);
		printf("Tamano %s \n", mod_size);
		printf("Usado Por: %s ", mod_usado_por);*/
		/*if (strcmp(mod_usado_por2,"-1") != 0) printf("%s\n", mod_usado_por2);
		else printf("\n");*/


	}

	fprintf(f,"%s", "</div>");
	fprintf(f,"%s", "</div>");
	fprintf(f,"%s", "</div>");

  //printf("ACA VA LA INFO DEL SISTEMA\n\n");


	fprintf(f,"%s", "</body>");
	fprintf(f,"%s\n", "</html>");

	fclose(f);

	fclose(fp);


	print_file("../archivos/lista_modulos_html.txt");
	return 0;
}
