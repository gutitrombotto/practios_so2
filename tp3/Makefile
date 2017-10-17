FUENTES=./test.c
FUENTEST1=./test1.c ./lectura_archivo.c ./funciones_estaciones.c ./funciones_servidor.c ./funciones_socket.c

F_GEN = ./src/funciones_genericas.c ./src/print_html.c ./src/lectura_archivo.c ./src/funciones_estaciones.c
F_MODULOS=./src/info_modulos.c ./src/funciones_genericas.c
F_SISTEMA=./src/info_sistema.c 
F_PRECIPDIA=./src/precipitacion_diaria.c 
F_PRECIPMEN=./src/precipitacion_mensual.c
F_PROM=./src/promedio_variable.c 
F_DESCARGA=./src/descarga-info.c 
F_SUBIDA=./src/subir-modulo.c 
CC = gcc -std=gnu11

CFLAGS=-I./includes -Wall -pedantic
#CFLAGS=-Wall -pedantic

#INCLUDES=-I../includes

#OBJETOS=$(SRCS:.c=.o)

M_MODULOS=./bin/modulos.cgi
M_SISTEMA=./bin/sistema.cgi
M_PRECIPDIA=./bin/precipitacion_diaria.cgi
M_PRECIPMEN=./bin/precipitacion_mensual.cgi
M_PROM=./bin/promedio_variable.cgi
M_DESC=./bin/descarga-info.cgi
M_SUB=./bin/subir-modulo.cgi


all_cgi: sistema precip_dia precip_men promedios modulos

modulos: $(OBJETOS)
	$(CC) $(F_MODULOS)  $(CFLAGS) -o $(M_MODULOS) $(OBJETOS)

sistema: $(OBJETOS)
	$(CC) $(F_SISTEMA) $(F_GEN) $(CFLAGS) -o $(M_SISTEMA) $(OBJETOS)

precip_dia: $(OBJETOS)
	$(CC) $(F_PRECIPDIA) $(F_GEN) $(CFLAGS) -o $(M_PRECIPDIA) $(OBJETOS)

precip_men: $(OBJETOS)
	$(CC) $(F_PRECIPMEN) $(F_GEN) $(CFLAGS) -o $(M_PRECIPMEN) $(OBJETOS)

promedios: $(OBJETOS)
	$(CC) $(F_PROM) $(F_GEN) $(CFLAGS) -o $(M_PROM) $(OBJETOS)


descarga: $(OBJETOS)
	$(CC) $(F_DESCARGA) $(F_GEN) $(CFLAGS) -o $(M_DESC) $(OBJETOS)


subida: $(OBJETOS)
	$(CC) $(F_SUBIDA) $(F_GEN) $(CFLAGS) -o $(M_SUB) $(OBJETOS)

cppcheck:
	cppcheck --enable=all --inconclusive --std=posix ../tp3 

copy_index:
	sudo cp index.html /var/www/html/tp3/

copy_files:
	sudo cp -R archivos/ /var/www/html/tp3/archivos/
copy_ksamp:
	sudo cp ./kernel_info/exe/ksamp /var/www/html/tp3/cgi/
copy_shell_scripts:
	sudo cp *.sh /var/www/html/tp3/
copy_vista_estaciones:
	sudo cp ./html/estaciones.html /var/www/html/tp3/html/
clean:
	$(RM) $(OBJETOS) $(MAIN)
prueba_test: $(OBJETOS)
	$(CC) ./src/prueba.c $(CFLAGS) -o prueba.o
