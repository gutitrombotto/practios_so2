OBJETOS=./object_files/main.o \
		./object_files/timeTools.o \
		./object_files/tools.o \
		./object_files/get_fromProc.o \
		./object_files/print_fromProc.o \


FUENTES=./src/main.c \
		./src/timeTools.c \
	    ./src/tools.c  \
	    ./src/get_fromProc.c \
	    ./src/print_fromProc.c \

CFLAGS=-I../includes -Wall -pedantic	

MAIN=./object_files/ksamp.o
all: compile link cppcheck

compile: $(FUENTES)
	gcc $(CFLAGS) -c ./src/main.c 			-o ./object_files/main.o
	gcc $(CFLAGS) -c ./src/timeTools.c 		-o ./object_files/timeTools.o
	gcc $(CFLAGS) -c ./src/tools.c 			-o ./object_files/tools.o
	gcc $(CFLAGS) -c ./src/get_fromProc.c 	-o ./object_files/get_fromProc.o
	gcc $(CFLAGS) -c ./src/print_fromProc.c -o ./object_files/print_fromProc.o

ksamp: $(OBJETOS)
	gcc $(FUENTES) $(CFLAGS) -o $(MAIN) $(OBJETOS)

link:
	gcc $(OBJETOS) -o exe/ksamp