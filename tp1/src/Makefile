FUENTES=./src/doc_parse.c
FUENTEST1=./test1.c ./lectura_archivo.c ./funciones_estaciones.c ./funciones_servidor.c ./funciones_socket.c

CFLAGS=-I../includes -Wall -pedantic

INCLUDES=-I../includes

#OBJETOS=$(SRCS:.c=.o)
FUENTEs_CLI=./cliente.c ./funciones_socket.c ./funciones_cliente.c

MAIN=./test
MAIN_CLI=./cliente

all_cliente: cliente_test cppcheck

all_servidor: t1 cppcheck

t1: $(OBJETOS)
	gcc $(FUENTEST1) $(CFLAGS) -o $(MAIN) $(OBJETOS)

cliente_test: $(OBJETOS)
	gcc $(FUENTEs_CLI) $(CFLAGS) -o $(MAIN_CLI) $(OBJETOS)	

normal:
	gcc test1.c -Wall -pedantic -o test1

bin: $(OBJETOS) 
	gcc $(FUENTES) $(CFLAGS) -o $(MAIN) $(OBJETOS)


cppcheck:
	cppcheck --enable=all --inconclusive --std=posix ../../tp1  

clean:
	$(RM) $(OBJETOS) $(MAIN)
