#include "funciones.h"
#include "listas.h"

void call_getopt(int argc, char** argv, int *m, char **archivo_entrada, char **archivo_salida){
	int c;
	char *m_value, *entrada_value, *salida_value;


	//Obtener parametros.
	opterr = 0;

	if(argc <= 6){
		printf("Se deben ingresar opciones (uso: -m <numero de marcos> -e <nombre archivo entrada> -o <nombre archivo salida>)\n");
		exit(1) ;
	}

	while((c = getopt(argc, argv, "m:e:o:")) != -1){
		switch (c) {
			case 'm':
				m_value = optarg;
				break;
			case 'e':
				entrada_value = optarg;
				break;
			case 'o':
				salida_value = optarg;
				break;
			case '?':
				if(optopt == 'm'){
					fprintf(stderr, "Opcion -m requiere un argumento.\n");
				}
				else if(optopt == 'e'){
					fprintf(stderr,"Opcion -e requiere un argumento\n");
				}
				else if(optopt == 'o'){
					fprintf(stderr,"Opcion -o requiere un argumento\n");
				}
				else if (isprint(optopt)) {
					fprintf(stderr, "Opcion -%c desconocida.\n", optopt);
				}
				else{
					fprintf(stderr, "Opcion desconocida '\\x%x'.\n", optopt);
				}
				exit(1);
			default:
				abort();
		}
	}

	//Procesar parametros.
	if(!isInt(m_value)){
		printf("El parametro ingresado para el numero de marcos no es valido\n");
		exit(1);
	}


	//retorno de parametros por referencia.
	*m = atoi(m_value);
	*archivo_entrada = entrada_value;
	*archivo_salida = salida_value;
}

int isInt(char *number){
 	int i, c;

 	for(i=0;i<strlen(number); i++){
    		c = number[i];
    		if(c < 48 || c > 57 || c == 0){
      			return 0;
    		}
  	}
  	return 1;
}

int getNumPaginas(char* nombreEntrada){
  FILE *file;
  int cantidad_entrada;
  char c;

	file = fopen(nombreEntrada, "r");
  if (file==NULL){
		printf("Archivo de entrada no existe\n");
		exit(1);
	}
  cantidad_entrada = 0;
	while (feof(file) == 0)
 	{
 		c = fgetc(file);
 		if(c == ',') {cantidad_entrada++;}
 	}
 	cantidad_entrada++;

  fclose(file);
  return cantidad_entrada;
}

int* getPaginas(char* entrada, int numPaginas){
	FILE *file;
	int *datos;
	char buffer[1000];
	char c;
	int i,j;

	file = fopen(entrada, "r");
	datos = (int*)malloc(numPaginas*sizeof(int));
	i = 0;
	j = 0;
	while (feof(file) == 0)
 	{
 		c = fgetc(file);
 		if (c != ',')
 		{
 			buffer[i] = c;
 			i++;
 		}
 		else
 		{
 			buffer[i] = '\0';
 			i = 0;
 			datos[j] = atoi(buffer);
 			j++;
 		}
 	}
 	buffer[i] = '\0';
	datos[j] = atoi(buffer);

	fclose(file);
	return datos;
}

float optimo(lista *L, char *archivo_entrada, char *archivo_salida)
{
	FILE *salida;
	char cadena[1000];
	int *paginas;
	int hits, miss, dato_actual, cantidad_marcos, m, k, big, numPaginas, i, j;
	int futuro[cantidad_marcos];
	float tasa_hits, tasa_miss;

	lista *aux = L;

	//Se obtienen las paginas
	numPaginas = getNumPaginas(archivo_entrada);
	paginas = getPaginas(archivo_entrada, numPaginas);


 	for(i = 0; i < numPaginas; i++){
 		printf("%d\n", paginas[i]);
 	}

	/*
	ahora tengo todos los datos del archivo de entrada guardados correctamente.
	Abro el archivo de salida para comenzar a escribir los resultados
	*/
	salida = fopen ( archivo_salida, "w" ); /* Como el optimo es el primero, hago que sobreescriba la salida */
	fputs("Algoritmo OPTIMO\n\n", salida);

	/* inicio las variables que voy a necesitar */
	cantidad_marcos = largo_lista(aux);
	m = 0;
	hits = 0;
	miss = 0;

	for(i = 0; i < cantidad_marcos; i++)
	{
		futuro[i] = 0;
	}

	for(i = 0; i < numPaginas; i++)
	{
		dato_actual = paginas[i];

		if(existe(dato_actual, aux) == 1)
		{
			hits++;

			for(k = 0; k < cantidad_marcos; k++)
			{
				if(recuperar_dato(k,aux) != -10000)
				{
					fputc((char)(recuperar_dato(k,aux) + 48) , salida);
				}
				else
				{
					fputc(' ', salida);
				}
				if(k != (cantidad_marcos-1))
				{
					fputc(' ', salida);
					fputc('-', salida);
					fputc(' ', salida);
				}
			}
			fputc('\n', salida);
			fputc('\n', salida);;

		}
		else{
			miss++;

			if(lleno(aux) != 1)
			{
				aux = insertar_dato(dato_actual, m, aux);
				m++;

				for(k = 0; k < cantidad_marcos; k++)
				{
					if(recuperar_dato(k,aux) != -10000)
					{
						fputc((char)(recuperar_dato(k,aux) + 48) , salida);
					}
					else
					{
						fputc(' ', salida);
					}
					if(k != (cantidad_marcos-1))
					{
						fputc(' ', salida);
						fputc('-', salida);
						fputc(' ', salida);
					}
				}
				fputc('\n', salida);
				fputc('\n', salida);
			}
			else
			{
				/* si no hay marcos disponibles entonces hay que comenzar el reemplazo */
				for(j = 0; j < cantidad_marcos; j++)
				{
					futuro[j] = mirar_futuro(i, numPaginas, paginas, recuperar_dato(j,aux));
				}
				big = mayor(futuro, cantidad_marcos);
				aux = insertar_dato(dato_actual, big, aux);

				 for(k = 0; k < cantidad_marcos; k++)
				{
					if(recuperar_dato(k,aux) != -10000)
					{
						fputc((char)(recuperar_dato(k,aux) + 48) , salida);
					}
					else
					{
						fputc(' ', salida);
					}
					if(k != (cantidad_marcos - 1))
					{
						fputc(' ', salida);
						fputc('-', salida);
						fputc(' ', salida);
					}
				}
				fputc('\n', salida);
				fputc('\n', salida);

			}
		}
	}

	tasa_miss = ((float)miss/(float)(miss + hits)) * 100;
	tasa_hits = ((float)hits/(float)(miss + hits)) * 100;

	sprintf(cadena, "tasa miss: %5.2f%c\n\n", tasa_miss,37);
	fputs(cadena,salida);

	sprintf(cadena, "tasa hits: %5.2f%c\n\n", tasa_hits,37);
	fputs(cadena,salida);

	fclose(salida);

	return tasa_miss;
}

int mirar_futuro(int inicio, int final,int paginas[], int dato)
{
	int i;
	int contador = 0;
	for(i = inicio; i < final; i++)
	{
		if(paginas[i] == dato)
			return contador;
		else
		{
			contador++;
		}
	}
	return 10000000;
}

int mayor(int arreglo[], int largo)
{
	int i, mayor;
	mayor = -10000000;

	for(i = 0; i < largo; i++)
	{
		if (arreglo[i] > mayor)
			mayor = arreglo[i];
	}

	for(i = 0; i < largo; i++)
	{
		if(arreglo[i] == mayor)
		{
			return i;
		}
	}

	return 0;
}

void fifo(lista *L, char *archivo_entrada, char *archivo_salida, float tasa_miss_optimo)
{
	FILE *salida;
	char cadena[1000];
	int *paginas;
	int hits, miss, dato_actual, cantidad_marcos, m, k, big, numPaginas, i, j;
	float tasa_hits, tasa_miss, diferencia;

	lista *aux = L;

	//Se obtienen las paginas
	numPaginas = getNumPaginas(archivo_entrada);
	paginas = getPaginas(archivo_entrada, numPaginas);


 	for(i = 0; i < numPaginas; i++){
 		printf("%d\n", paginas[i]);
 	}

	/*
	ahora tengo todos los datos del archivo de entrada guardados correctamente.
	Abro el archivo de salida para comenzar a escribir los resultados
	*/
	salida = fopen ( archivo_salida, "a" ); /* Ahora lo abro en modo append para no sobreescribir */
	fputs("Algoritmo FIFO\n\n", salida);

	/* creo variables a utilizar */
	miss = 0;
	hits = 0;
	m = 0;
	cantidad_marcos = largo_lista(aux);

	for(i = 0; i < numPaginas; i++)
	{
		dato_actual = paginas[i];

		if(existe(dato_actual, aux) == 1)
		{
			hits++;

			for(k = 0; k < cantidad_marcos; k++)
			{
				if(recuperar_dato(k,aux) != -10000)
				{
					fputc((char)(recuperar_dato(k,aux) + 48) , salida);
				}
				else
				{
					fputc(' ', salida);
				}
				if(k != (cantidad_marcos-1))
				{
					fputc(' ', salida);
					fputc('-', salida);
					fputc(' ', salida);
				}
			}
			fputc('\n', salida);
			fputc('\n', salida);;
		}
		else
		{
			miss++;

			if(lleno(aux) != 1)
			{
				aux = insertar_dato(dato_actual, m, aux);
				m = (m+1)%cantidad_marcos;

				for(k = 0; k < cantidad_marcos; k++)
				{
					if(recuperar_dato(k,aux) != -10000)
					{
						fputc((char)(recuperar_dato(k,aux) + 48) , salida);
					}
					else
					{
						fputc(' ', salida);
					}
					if(k != (cantidad_marcos-1))
					{
						fputc(' ', salida);
						fputc('-', salida);
						fputc(' ', salida);
					}
				}
				fputc('\n', salida);
				fputc('\n', salida);
			}
			else
			{
				/* si los marcos estan llenos entonces comienza el reemplazo */
				aux = insertar_dato(dato_actual, m, aux);
				m = (m+1)%cantidad_marcos;

				for(k = 0; k < cantidad_marcos; k++)
				{
					if(recuperar_dato(k,aux) != -10000)
					{
						fputc((char)(recuperar_dato(k,aux) + 48) , salida);
					}
					else
					{
						fputc(' ', salida);
					}
					if(k != (cantidad_marcos-1))
					{
						fputc(' ', salida);
						fputc('-', salida);
						fputc(' ', salida);
					}
				}
				fputc('\n', salida);
				fputc('\n', salida);
			}
		}
	}

	tasa_miss = ((float)miss/(float)(miss + hits)) * 100;
	tasa_hits = ((float)hits/(float)(miss + hits)) * 100;

	sprintf(cadena, "tasa miss: %5.2f%c\n\n", tasa_miss,37);
	fputs(cadena,salida);

	sprintf(cadena, "tasa hits: %5.2f%c\n\n", tasa_hits,37);
	fputs(cadena,salida);

	diferencia = tasa_miss - tasa_miss_optimo;
	sprintf(cadena, "%5.2f%c peor que el algoritmo óptimo\n\n",diferencia, 37);
	fputs(cadena,salida);

	fclose(salida);
}

void LRU(lista *L, char *archivo_entrada, char *archivo_salida, float tasa_miss_optimo){

	FILE *salida;
	char cadena[1000];
	int *usados;
	int *paginas;
	int hits, miss, dato_actual, cantidad_marcos, m, k, pos, numPaginas, i, j, index;
	float tasa_hits, tasa_miss, diferencia;

	lista *aux = L;

	//Se obtienen las paginas
	numPaginas = getNumPaginas(archivo_entrada);
	paginas = getPaginas(archivo_entrada, numPaginas);
	usados = (int*)malloc(numPaginas*sizeof(int));

 	for(i = 0; i < numPaginas; i++){
 		printf("%d\n", paginas[i]);
 	}

	/*
	ahora tengo todos los datos del archivo de entrada guardados correctamente.
	Abro el archivo de salida para comenzar a escribir los resultados
	*/
	salida = fopen ( archivo_salida, "a" ); /* Ahora lo abro en modo append para no sobreescribir */
	fputs("Algoritmo LRU\n\n", salida);

	/* creo variables a utilizar */
	miss = 0;
	hits = 0;
	m = 0;
	index = 0;
	cantidad_marcos = largo_lista(aux);

	for (i = 0; i < numPaginas; ++i)
	{
		dato_actual = paginas[i];
		if(existe(dato_actual, aux)){
			hits++;
			for(j=0;j<numPaginas;j++){
				if(dato_actual == usados[j]){
					usados[j] = -1;//fue usado recientenmente
					usados[index] = dato_actual;
					index++;
					break;
				}
			}
			for(k = 0; k < cantidad_marcos; k++)
			{
				if(recuperar_dato(k,aux) != -10000)
				{
					fputc((char)(recuperar_dato(k,aux) + 48) , salida);
				}
				else
				{
					fputc(' ', salida);
				}
				if(k != (cantidad_marcos-1))
				{
					fputc(' ', salida);
					fputc('-', salida);
					fputc(' ', salida);
				}
			}
			fputc('\n', salida);
			fputc('\n', salida);;
		}
		else{
			miss++;

			if(lleno(aux) != 1){
				aux = insertar_dato(dato_actual, m, aux);
				usados[index] = dato_actual;
				index++;
				m = (m+1)%cantidad_marcos;

				for(k = 0; k < cantidad_marcos; k++)
				{
					if(recuperar_dato(k,aux) != -10000)
					{
						fputc((char)(recuperar_dato(k,aux) + 48) , salida);
					}
					else
					{
						fputc(' ', salida);
					}
					if(k != (cantidad_marcos-1))
					{
						fputc(' ', salida);
						fputc('-', salida);
						fputc(' ', salida);
					}
				}
				fputc('\n', salida);
				fputc('\n', salida);
			}
			else{
				/* si los marcos estan llenos entonces comienza el reemplazo */
				for(j=0;j<numPaginas;j++){
					if(usados[j] != -1){
						pos = posicion(usados[j], aux);
						aux = insertar_dato(dato_actual, pos, aux);
						usados[j] = -1;
						break;
					}
				}
				for(k = 0; k < cantidad_marcos; k++)
				{
					if(recuperar_dato(k,aux) != -10000)
					{
						fputc((char)(recuperar_dato(k,aux) + 48) , salida);
					}
					else
					{
						fputc(' ', salida);
					}
					if(k != (cantidad_marcos-1))
					{
						fputc(' ', salida);
						fputc('-', salida);
						fputc(' ', salida);
					}
				}
				fputc('\n', salida);
				fputc('\n', salida);
			}
		}
	}

	tasa_miss = ((float)miss/(float)(miss + hits)) * 100;
	tasa_hits = ((float)hits/(float)(miss + hits)) * 100;

	sprintf(cadena, "tasa miss: %5.2f%c\n\n", tasa_miss,37);
	fputs(cadena,salida);

	sprintf(cadena, "tasa hits: %5.2f%c\n\n", tasa_hits,37);
	fputs(cadena,salida);

	diferencia = tasa_miss - tasa_miss_optimo;
	sprintf(cadena, "%5.2f%c peor que el algoritmo óptimo\n\n",diferencia, 37);
	fputs(cadena,salida);

	fclose(salida);
}

void reloj(lista *L, char *archivo_entrada, char *archivo_salida, float tasa_miss_optimo){

	lista *aux = L;

	/* abro el archivo de entrada */
	FILE *entrada;
	entrada = fopen ( archivo_entrada, "r" );
	if (entrada==NULL)
	{
		printf("Archivo de entrada no existe\n");
		exit (1);
	}

	/*
	cuento las comas del archivo de entrada, ya que la cantidad
	de elementos son la cantidad de comas + 1
	*/
	int cantidad_entrada = 0;
	char c;
	while (feof(entrada) == 0)
 	{
 		c = fgetc(entrada);
 		if(c == ',') {cantidad_entrada++;}
 	}
 	cantidad_entrada++;
 	rewind(entrada);

 	/*
	ahora si obtengo los datos del archivo de entrada
	y los guardo en un arreglo correspondiente.
 	*/
 	int datos[cantidad_entrada];
 	int i,j;
 	i = 0;
 	j = 0;
 	char entero[10000];
 	while (feof(entrada) == 0)
 	{
 		c = fgetc(entrada);
 		if (c != ',')
 		{
 			entero[i] = c;
 			i++;
 		}
 		else
 		{
 			entero[i] = '\0';
 			i = 0;
 			datos[j] = atoi(entero);
 			j++;
 		}
 	}
 	entero[i] = '\0';
	datos[j] = atoi(entero);


	/*
	ahora tengo todos los datos del archivo de entrada guardados correctamente.
	Abro el archivo de salida para comenzar a escribir los resultados
	*/
	FILE *salida;
	salida = fopen ( archivo_salida, "a" ); /* Ahora lo abro en modo append para no sobreescribir */
	fputs("Algoritmo Reloj\n\n", salida);

	/* creo variables a utilizar */
	int miss = 0;
	int hits = 0;
	int m = 0;
	int k;
	char cadena[1000];
	int dato_actual;
	int cantidad_marcos = largo_lista(aux);
	for (i = 0; i < cantidad_entrada; ++i)
	{
		dato_actual = datos[i];
		if(existe(dato_actual, aux)){
			hits++;
			for(k = 0; k < cantidad_marcos; k++)
			{
				if(recuperar_dato(k,aux) != -10000)
				{
					fputc((char)(recuperar_dato(k,aux) + 48) , salida);
				}
				else
				{
					fputc(' ', salida);
				}
				if(k != (cantidad_marcos-1))
				{
					fputc(' ', salida);
					fputc('-', salida);
					fputc(' ', salida);
				}
			}
			fputc('\n', salida);
			fputc('\n', salida);;
		}
		else{
			miss++;

			if(lleno(aux) != 1){
				aux = insertar_dato(dato_actual, m, aux);
				m = (m+1)%cantidad_marcos;

				for(k = 0; k < cantidad_marcos; k++)
				{
					if(recuperar_dato(k,aux) != -10000)
					{
						fputc((char)(recuperar_dato(k,aux) + 48) , salida);
					}
					else
					{
						fputc(' ', salida);
					}
					if(k != (cantidad_marcos-1))
					{
						fputc(' ', salida);
						fputc('-', salida);
						fputc(' ', salida);
					}
				}
				fputc('\n', salida);
				fputc('\n', salida);
			}
			else{
				/* si los marcos estan llenos entonces comienza el reemplazo */

			}
		}
	}
}
