# GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira

all: programa1 programa2 programa3

programa1: programa1.o Pilha.o
	gcc -o programa1 programa1.o Pilha.o

programa1.o: programa1.c Pilha.h
	gcc -c programa1.c -Wall -Wextra -g

programa2: programa2.o Pilha.o
	gcc -o programa2 programa2.o Pilha.o -lm

programa2.o: programa2.c Pilha.h
	gcc -c programa2.c -Wall -Wextra -g

programa3: programa3.o Pilha.o
	gcc -o programa3 programa3.o Pilha.o

programa3.o: programa3.c Pilha.h
	gcc -c programa3.c -Wall -Wextra -g

Pilha.o: Pilha.c Pilha.h
	gcc -c Pilha.c -Wall -Wextra -g

clean:
	rm -f programa1 programa2 programa3 *.o