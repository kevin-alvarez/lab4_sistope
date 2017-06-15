#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "listas.h"

//////// --ESTRUCTURAS-- ///////

//////// -- VAR. GLOBALES -- ///////

//////// --FUNCIONES-- ////////
/*
    Procedimiento que hace la llamada a getopt para obtener las opciones y
    parametros ingresados por la terminal.
    @parametros ...
*/
void call_getopt(int argc, char** argv, int *m, char **archivo_entrada, char **archivo_salida);

/*
    Funcion que verifica si un string representa un numero o no, entrega 0 si es
    un numero y 1 si no.
    @param number string para verificar.
    @return resultado de la verificacion.
*/
int isInt(char *number);

/*
funcion que aplica el algoritmo de reemplazo OPTIMO, el cual mira que página
esta más lejana a ser referenciada, y elije esta para reemplazar.
En caso de que varias paginas no se referencien en la misma cantidad de tiempos,
entonces se reemplaza cualquiera.
@entrada: 	lista L correspondiente a los marcos
		el nombre del archivo de entrada
		el nombre del archivo de salida
@salida: 	devuelve la tasa de miss de este algoritmo, para futuros calculos
*/
float optimo(lista *L, char *archivo_entrada, char *archivo_salida);

/*
funcion que mira hacia el futuro las paginas en el algoritmo optimo
para saber cual reemplazar
@entrada: 	inicio indicando en que pagina actual vamos
		final indicando hasta que paginas existen
		las paginas en si
		y el dato que se esta buscando hacia adelante
@salida: el numero de turnos en que se demora en aparecer la pagina buscada
	si la pagina no esta, retorna un numero muy grande.
*/
int mirar_futuro(int inicio, int final,int paginas[], int dato);

/*
funcion que entrega la posicion del numero mayor de un arreglo de numeros
@entrada: el arreglo de numeros y el largo de este
@salida: la posicion del numero mayor. Si hay mas de uno que cumple la caracteristica, entrega el primero en aparecer
*/
int mayor(int arreglo[], int largo);

#endif
