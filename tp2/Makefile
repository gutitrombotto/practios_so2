CC = gcc
RM = rm -f
F_MAIN=./src/main.c
EXE_MAIN=./bin/main

CFLAGS=-I../includes -Wall -pedantic -lm
INCLUDES=-I../includes

OBJETOS=$(SRCS:.c=.o)

all: clean main cppcheck
main: $(OBJETOS)
	$(CC) $(F_MAIN) $(CFLAGS) -o $(EXE_MAIN) $(OBJETOS)

cppcheck:
	cppcheck --enable=all --inconclusive --std=posix ../tp2  

clean:
	$(RM) $(OBJETOS) $(EXE_MAIN)
