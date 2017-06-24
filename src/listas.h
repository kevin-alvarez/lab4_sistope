#ifndef LISTAS_H
#define LISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

//////// --ESTRUCTURAS-- ///////
/*
    Estructura principal de la lista enlazada circular.
*/
struct celda{
    int dato;   /* valor del número de página */
    int final;  /* valor 1 para indicar que el nodo es el final de la lista,*/
    struct celda *sgte;
};
typedef struct celda lista;

//////// --FUNCIONES-- ///////
/*
    Funcion que crea una lista vacia.
    @return Lista vacia.
*/
lista *crear();

/*
    Funcion que inserta un nodo al final de la lista.
    @param L Lista en la cual insertar nodo.
    @return Misma lista L pero con un nodo vacio al final de esta.
*/
lista *insertar_nodo(lista *L);

/*
    Funcion que obtiene el largo de la lista.
    @param L Lista de la cual obtener el largo.
    @return Largo de la lista ingresada.
*/
int largo_lista(lista *L);

/*
    Funcion que inserta un elemento de una posicion de una lista.
    @param x Elemento a ingresar en la lista.
    @param p Posicion donde ingresar el elemento.
    @param L Lista en la cual se ingresa el elemento.
    @return Misma lista L pero con un el dato insertado.
*/
lista *insertar_dato(int x, int p, lista *L);

/*
    Procedimiento que imprime por pantalla una lista.
    @param L Lista para mostrar.
*/
void mostrar(lista *L);

/*
    Funcion que recupera un elemento de una posicion de una lista.
    @param p Posicion donde recuperar el elemento.
    @param L Lista de la cual se recupera el elemento.
    @return elemento recuperado de la lista.
*/
int recuperar_dato(int p, lista *L);

/*
    Procedimiento que destruye una lista y libera la memoria ocupada por esta.
    @param L Lista para ser destruida.
*/
void destruir(lista *L);

/*
    Funcion que comprueba si existe un elemento en una lista.
    @param x Elemento a verificar en lista.
    @param L Lista en la cual se verfica el elemento.
    @return resultado de la verificacion, 1 si existe, 0 si no.
*/
int existe(int x, lista *L);

/*
    Funcion que comprueba si una lista esta llena(dado que el conjunto residente puede estar lleno).
    @param L Lista a verificar.
    @return resultado de la verificacion, 1 si esta llena, 0 si no.
*/
int lleno(lista *L);

/*
    Funcion que entrega la posicion en que se encuentra un dato en una lista.
    @param x Elemento para obtener la posicion.
    @param L Lista en la cual se busca el elemento.
    @return Posicion del elemento buscado, retorna un numero invalido si no esta.
*/
int posicion(int x, lista *L);

#endif
