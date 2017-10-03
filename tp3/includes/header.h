/*! \file header.h
    \brief Este archivo contiene las funciones de lectura del archivo de datos meteorologicos
*/

#ifndef HEADER_H
#define HEADER_H


const char * head[] = {
	"<!DOCTYPE html>",
	"<html lang=\"en\">",
	"<head> \n",
	"<meta charset=\"utf-8\" \n",
//	"<title> Sistemas Operativos 2 </title> \n",
	"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n",
	"<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">\n",
	"<link rel=\"stylesheet\" href=\"https://code.jquery.com/ui/1.12.1/themes/base/jquery-ui.css\">\n",
	"</head>\n",
	NULL
};

const char * error_eleccion_funcion = "<h2 class=\"text-center\">Funcion Seleccionada no valida</h2>";
const char * nav_bar[] = {
	"<nav class=\"navbar navbar-inverse navbar-default navbar-static-top\">",
	"<div class=\"container-fluid\">",
	"<div class=\"navbar-header\">",
	"<button type=\"button\" class=\"navbar-toggle collapsed\" data-toggle=\"collapse\" data-target=\"#navbar\" aria-expanded=\"false\" aria-controls=\"navbar\">",
	"<span class=\"sr-only\">Mostrar Menú</span>",
	"<span class=\"icon-bar\"></span>",
	"<span class=\"icon-bar\"></span>",
	"<span class=\"icon-bar\"></span>",
	"</button>",
	"<a class=\"navbar-brand\" href=\"#\">Trabajo Practico 3: Sistemas Operativos II</a>",
	"</div>",
	"<div id=\"navbar\" class=\"navbar-collapse collapse\">",
	"<ul class=\"nav navbar-nav\">",
	"<li><a href=\"/tp3/index.html\">Inicio</a></li>",
	"</ul>",
	
	"<ul class=\"nav navbar-nav navbar-right\">",
	"<li><a href=\"/tp3/cgi/sistema.cgi\">Info Sistema</a></li>",
	"<li><a href=\"/tp3/html/estaciones.html\">Estaciones Meteorologicas</a></li>",
     "<li><a href=\"/tp3/cgi/modulos.cgi\">Drivers</a></li>",
	"<li><a href=\"#\">Agustin Trombotto</a></li>",
	"</ul>",
	"</div>",
	"</div>",
	"</nav>",
	NULL
};

#endif