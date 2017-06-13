#include "funciones.h"
#include "listas.h"

lista *crear()
{
	/* el primer nodo de la lista es la cabecera de la lista */
	lista *L=malloc(sizeof(lista));
	L->final = 1;
	L->dato = -10000;
	L->sgte=L;
	return L;
}

lista *insertar_nodo(lista *L)
{	
	lista *aux=L;
	lista *cabecera = L;

	while(aux->final != 1)
	{
		aux = aux->sgte;
	}

	aux->final = 0;
	aux->sgte = crear();
	aux->sgte->dato = -10000;
	aux->sgte->final = 1;
	aux->sgte->sgte = cabecera;

	return L;
}

int largo_lista(lista *L)
{	
	/* 
	la cabecera no cuenta para el largo de una lista.
	*/
	lista *aux = L;
	int contador = 0;

	while(aux->final != 1)
	{
		contador++;
		aux = aux->sgte;
	}

	return contador;
}

lista *insertar_dato(int x, int p, lista *L){

	/* El primer elemento de la lista que no sea la cabecera tiene posicion 0 */
	lista *aux = L->sgte;
	int largo = largo_lista(L);
	int i;

	if(p >= largo)
	{	
		/*  Si la posicion a insertar el dato supera el largo de la lista */
		printf("No se ha insertado el dato\n");
		return L;
	}

	for(i = 0; i < p; i++)
	{
		aux = aux->sgte;
	}

	aux->dato = x;
	return L;
}

void mostrar(lista *L)
{
	lista *aux=L->sgte;
	while(aux->final != 1){
		printf("%i - ", aux->dato);
		aux=aux->sgte;
	}
	printf("%i - ", aux->dato);
	printf("repeat\n");
}

int recuperar_dato(int p, lista *L)
{
	/* El primer elemento de la lista que no sea la cabecera tiene posicion 0 */
	lista *aux = L->sgte;
	int largo = largo_lista(L);
	int i;

	if(p >= largo)
	{	
		/*  Si la posicion a recuperar el dato supera el largo de la lista */
		printf("posicion invalida\n");
		return -10000;
	}

	for(i = 0; i < p; i++)
	{
		aux = aux->sgte;
	}

	return aux->dato;
}

void destruir(lista *L)
{
	lista *aux=L;
	lista *aux2;
	while(aux->final != 1)
	{
		aux2 = aux;
		aux = aux->sgte;
		free(aux2);
	}
	free(aux);
}

int existe(int x, lista *L)
{
	lista *aux = L->sgte;
	while(aux->final != 1)
	{
		if(x == aux->dato){ return 1; }
		aux = aux -> sgte;
	}
	if(x == aux->dato){ return 1; }
	return 0;
}

int lleno(lista *L)
{
	if(largo_lista(L) == 0){return 1;}

	lista *aux = L->sgte;
	while(aux->final != 1){
		if(aux->dato == -10000){ return 0; }
		aux = aux->sgte;
	}
	if(aux->dato == -10000){ return 0;}

	return 1;
}