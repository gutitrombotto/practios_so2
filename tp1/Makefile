FUENTES=./src/doc_parse.c

CFLAGS=-I../includes -Wall -pedantic

INCLUDES=-I../includes

#OBJETOS=$(SRCS:.c=.o)
FUENTES_SV=./src/servidor.c ./src/lectura_archivo.c ./src/funciones_estaciones.c ./src/funciones_servidor.c ./src/funciones_socket.c
FUENTEs_CLI=./src/cliente.c ./src/funciones_socket.c ./src/funciones_cliente.c

MAIN_SV=./bin/servidor
MAIN_CLI=./bin/cliente

server: $(OBJETOS)
	gcc $(FUENTES_SV) $(CFLAGS) -o $(MAIN_SV) $(OBJETOS)

client: $(OBJETOS)
	gcc $(FUENTEs_CLI) $(CFLAGS) -o $(MAIN_CLI) $(OBJETOS)	

normal:
	gcc test1.c -Wall -pedantic -o test1

bin: $(OBJETOS) 
	gcc $(FUENTES_SV) $(CFLAGS) -o $(MAIN_SV) $(OBJETOS)
	gcc $(FUENTEs_CLI) $(CFLAGS) -o $(MAIN_CLI) $(OBJETOS)


cppcheck:
	cppcheck --enable=all --inconclusive --std=posix ../tp1  

clean:
	$(RM) $(OBJETOS) $(MAIN)
