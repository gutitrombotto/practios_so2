CC = gcc
RM = rm -f
F_MAIN=./src/main.c
F_MAIN_OMP=./src/main_opmp.c

EXE_MAIN=./bin/main
EXE_MAIN_OMP=./bin/main_mp

CFLAGS=-I../includes -Wall -pedantic -lm
INCLUDES=-I../includes

OMP_FLAG=-fopenmp
OBJETOS=$(SRCS:.c=.o)

all: clean main cppcheck

main: $(OBJETOS)
	$(CC) $(F_MAIN) $(CFLAGS) -o $(EXE_MAIN) $(OBJETOS)

main_openmp: $(OBJETOS)
	$(CC) $(F_MAIN_OMP) $(CFLAGS) $(OMP_FLAG) -o $(EXE_MAIN_OMP) $(OBJETOS)
cppcheck:
	cppcheck --enable=all --inconclusive --std=posix ../tp2  

clean:
	$(RM) $(OBJETOS) $(EXE_MAIN)
