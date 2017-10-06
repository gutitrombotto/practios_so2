FUENTES=./test.c
FUENTEST1=./test1.c ./lectura_archivo.c ./funciones_estaciones.c ./funciones_servidor.c ./funciones_socket.c

F_GEN = ./src/funciones_genericas.c ./src/print_html.c ./src/lectura_archivo.c ./src/funciones_estaciones.c
F_MODULOS=./src/info_modulos.c ./src/funciones_genericas.c
F_SISTEMA=./src/info_sistema.c 
F_PRECIPDIA=./src/precipitacion_diaria.c 
F_PRECIPMEN=./src/precipitacion_mensual.c
F_PROM=./src/promedio_variable.c 
F_DESCARGA=./src/descarga-info.c 
CFLAGS=-I./includes -Wall -pedantic
#CFLAGS=-Wall -pedantic

#INCLUDES=-I../includes

#OBJETOS=$(SRCS:.c=.o)
FUENTEs_CLI=./cliente.c ./funciones_socket.c ./funciones_cliente.c

MAIN=./test.cgi
MAIN_CLI=./cliente


M_MODULOS=./bin/modulos.cgi
M_SISTEMA=./bin/sistema.cgi
M_PRECIPDIA=./bin/precipitacion_diaria.cgi
M_PRECIPMEN=./bin/precipitacion_mensual.cgi
M_PROM=./bin/promedio_variable.cgi
M_DESC=./bin/descarga-info.cgi


all_cgi: sistema precip_dia precip_men promedios modulos
modulos: $(OBJETOS)
	gcc $(F_MODULOS)  $(CFLAGS) -o $(M_MODULOS) $(OBJETOS)

sistema: $(OBJETOS)
	gcc $(F_SISTEMA) $(F_GEN) $(CFLAGS) -o $(M_SISTEMA) $(OBJETOS)

precip_dia: $(OBJETOS)
	gcc $(F_PRECIPDIA) $(F_GEN) $(CFLAGS) -o $(M_PRECIPDIA) $(OBJETOS)

precip_men: $(OBJETOS)
	gcc $(F_PRECIPMEN) $(F_GEN) $(CFLAGS) -o $(M_PRECIPMEN) $(OBJETOS)

promedios: $(OBJETOS)
	gcc $(F_PROM) $(F_GEN) $(CFLAGS) -o $(M_PROM) $(OBJETOS)


descarga: $(OBJETOS)
	gcc $(F_DESCARGA) $(F_GEN) $(CFLAGS) -o $(M_DESC) $(OBJETOS)

cppcheck:
	cppcheck --enable=all --inconclusive --std=posix ../tp3 


clean:
	$(RM) $(OBJETOS) $(MAIN)
