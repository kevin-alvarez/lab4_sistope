#include "funciones.h"
#include "listas.h"

/*
	Laboratorio 4 - Sistemas operativos
  	USACH 1-2017
  	Integrantes:
  	- Kevin Alvarez
  	- Javier Vasquez
  	Descripción:
  	El presente laboratorio consiste en recrear politicas
  	de reemplazo de páginas, y establecer diferencias.
*/

int main(int argc, char** argv)
{

	int m;
	char *archivo_entrada = (char*)malloc(sizeof(char) * 100);
	char *archivo_salida = (char*)malloc(sizeof(char) * 100);

	/*  Realizo el get opt de los valores de entrada hechos por la consola */
	call_getopt(argc, argv, &m, &archivo_entrada, &archivo_salida);

	/*
	printf("numero de marcos: %d\nnombre archivo de entrada: %s\nnombre archivo de salida: %s\n", m,archivo_entrada,archivo_salida);
	*/

	/*
	PROBANDO EL TDA

	lista *L = crear();
	int i;
	for(i < 0; i < 3; i++){
		L = insertar_nodo(L);	
	}
	insertar_dato(69,0,L);
	insertar_dato(2,1,L);
	insertar_dato(3,2,L);
	mostrar(L);
	printf("%d\n", recuperar_dato(0,L));
	*/

	/*
	creo la lista vacia con el numero de marcos disponibles
	*/
	lista *L = crear();
	int i;
	for(i < 0; i < m; i++){
		L = insertar_nodo(L);	
	}

	int tasa_miss_optimo;
	//tasa_miss_optimo = optimo(L, archivo_entrada,archivo_salida,);


	return 0;
}

