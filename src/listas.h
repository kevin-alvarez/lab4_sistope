#ifndef LISTAS_H
#define LISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

//////// --ESTRUCTURAS-- ///////
struct nodoC{
  int dato;
  struct nodoC *anterior;
  struct nodoC *siguiente;
};

typedef struct listaC{
  int largo;
  struct nodoC *cabeza;
}listaC;

//////// --FUNCIONES-- ///////
int length(listaC *L);
int get(int index, listaC *L);
void insert(listaC *L);
void remove(int index, listaC *L);

#endif
