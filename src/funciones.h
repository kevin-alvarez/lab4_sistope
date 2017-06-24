#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "listas.h"

//////// --FUNCIONES-- ////////
/*
    Procedimiento que hace la llamada a getopt para obtener las opciones y
    parametros ingresados por la terminal.
    @param argc cantidad de parametros ingresados por consola.
    @param argv arreglo con los parametros ingresados por consola.
    @param n paso por referencia para obtener el tamaño del tablero.
    @param d paso por referencia para obtener la bandera para mostrar el resumen de los guerreros.
    @param nombreArchivo paso por referencia para obtener el nombre del archivo ingresado.
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
    Funcion que aplica el algoritmo de reemplazo OPTIMO, el cual mira que página
    esta más lejana a ser referenciada, y elije esta para reemplazar.
    En caso de que varias paginas no se referencien en la misma cantidad de tiempos,
    entonces se reemplaza cualquiera.
    @param L Lista correspondiente a los marcos.
    @param archivo_entrada Nombre del archivo de entrada.
    @param archivo_salida Nombre del archivo de salida.
    @return Tasa de miss de este algoritmo, para futuros calculos.
*/
float optimo(lista *L, char *archivo_entrada, char *archivo_salida);

/*
    Funcion que mira hacia el futuro las paginas en el algoritmo optimo
    para saber cual reemplazar
    @param inicio Inicio indicando en que pagina actual vamos.
    @param final Final indicando hasta que paginas existen.
    @param paginas Las paginas en si.
    @param dato dato que se esta buscando hacia adelante.
    @return Numero de turnos en que se demora en aparecer la pagina buscada si la pagina no esta, retorna un numero muy grande.
*/
int mirar_futuro(int inicio, int final, int paginas[], int dato);

/*
    Funcion que entrega la posicion del numero mayor de un arreglo de numeros.
    @param arreglo Arreglo de numeros y el largo de este.
    @return Posicion del numero mayor. Si hay mas de uno que cumple la caracteristica, entrega el primero en aparecer.
*/
int mayor(int arreglo[], int largo);

/*
    Funcion que obtiene el numero de paginas desde a un archivo de entrada con las paginas.
    @param nombreEntrada nombre del archivo de entrada con las paginas.
    @return Numero de paginas.
*/
int getNumPaginas(char* nombreEntrada);

/*
    Funcion que obtiene las paginas desde un archivo de entrada.
    @param nombreEntrada nombre del archivo de entrada con las paginas.
    @param numPaginas cantidad de paginas que existen en el archivo.
    @return arreglo con las paginas.
*/
int* getPaginas(char* entrada, int numPaginas);

/*
    Procedimiento que aplica el algoritmo de reemplazo FIFO, el cual reemplaza la pagina mas antigua que entro.
    @param L Lista correspondiente a los marcos.
    @param archivo_entrada Nombre del archivo de entrada.
    @param archivo_salida Nombre del archivo de salida.
    @param tasa_miss_optimo Tasa de miss obtenida del algoritmo de reemplazo OPTIMO para realizar comparaciones.
*/
void fifo(lista *L, char *archivo_entrada, char *archivo_salida, float tasa_miss_optimo);

/*
    Procedimiento que aplica el algoritmo de reemplazo LRU, el cual reemplaza la pagina menos recientenmente usada.
    @param L Lista correspondiente a los marcos.
    @param archivo_entrada Nombre del archivo de entrada.
    @param archivo_salida Nombre del archivo de salida.
    @param tasa_miss_optimo Tasa de miss obtenida del algoritmo de reemplazo OPTIMO para realizar comparaciones.
*/
void LRU(lista *L, char *archivo_entrada, char *archivo_salida, float tasa_miss_optimo);

/*
    Algoritmo reloj no implementado.
*/
//void reloj(lista *L, char *archivo_entrada, char *archivo_salida, float tasa_miss_optimo);

#endif
