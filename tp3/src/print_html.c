#include <stdio.h>
#include <string.h>
#include "../includes/header.h"

void cargar_header()
{
	for (int i = 0; head[i] != NULL; ++i)
	{
		printf("%s", head[i]);

	}
}

void cargar_navbar()
{
	for (int i = 0; nav_bar[i] != NULL; ++i)
	{
		printf("%s", nav_bar[i]);

	}
}


void error_eleccion()
{
	printf("%s\n", error_eleccion_funcion);
}
