all:
	gcc -Wall -o grafo.o -c grafo.c
	gcc -Wall -o fila.o -c fila.c
	gcc -Wall -o pilha.o -c pilha.c
	gcc -Wall -o main grafo.o fila.o pilha.o main.c

run:
	./main
