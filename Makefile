CC=gcc
route=src/
libs=

all: main.o functions.o
	$(CC) main.o functions.o listas.o -o lab3 -Wall $(libs)
	rm main.o functions.o listas.o

main.o: $(route)main.c
	$(CC) -c $(route)main.c

functions.o: $(route)functions.c
	$(CC) -c $(route)functions.c

listas.o: $(route)listas.c
		$(CC) -c $(route)listas.c
