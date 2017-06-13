#ifndef LISTAS_H
#define LISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

//////// --ESTRUCTURAS-- ///////
struct celda{
    int dato;   /* valor del número de página */
    int final;  /* valor 1 para indicar que el nodo es el final de la lista,*/
    struct celda *sgte;
};
typedef struct celda lista;

//////// --FUNCIONES-- ///////
/*
crea una lista vacia
@salida: una lista vacia
*/
lista *crear();

/*
inserta un nodo al final de la lista
@entrada: una lista L
@salida: misma lista L pero con un nodo vacio al final de esta.
*/
lista *insertar_nodo(lista *L);

/*
obtiene el largo de la lista
@entrada: una lista L
@salida: el largo de la lista
*/
int largo_lista(lista *L);

/*
inserta un dato x en la posicion p de la lista L
*/
lista *insertar_dato(int x, int p, lista *L);

/*
muestra la lista
mas que nada esto es para tener un seguimiento de los datos
@entrada: la lista L a mostrar
*/
void mostrar(lista *L);

/*

*/
int recuperar_dato(int p, lista *L);

/*
destruye la lista L
@entrada: la lista L a borrar
*/
void destruir(lista *L);

/*
verifica si existe un elemento x en la lista L.
@entrada: elemento x a verificar, y lista L en la cual buscar.
@salida: 1 si existe el elemento, y 0 en caso contrario.
*/
int existe(int x, lista *L);

#endif
