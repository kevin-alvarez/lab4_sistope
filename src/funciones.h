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

*/
int optimo(lista *L, char *archivo_entrada, char *archivo_salida);

#endif
