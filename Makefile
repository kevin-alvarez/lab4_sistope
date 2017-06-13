CC=gcc
route=src/
libs=

all: main.o funciones.o listas.o
	$(CC) main.o funciones.o listas.o -o politica -Wall $(libs)
	rm main.o funciones.o listas.o

main.o: $(route)main.c
	$(CC) -c $(route)main.c

funciones.o: $(route)funciones.c
	$(CC) -c $(route)funciones.c

listas.o: $(route)listas.c
		$(CC) -c $(route)listas.c
