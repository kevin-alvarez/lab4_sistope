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

float optimo(lista *L, char *archivo_entrada, char *archivo_salida)
{
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
 	int i,j = 0;
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
 	for(i = 0; i < cantidad_entrada; i++){
 		printf("%d\n", datos[i]);
 	}
	*/

	/* 
	ahora tengo todos los datos del archivo de entrada guardados correctamente.
	Abro el archivo de salida para comenzar a escribir los resultados
	*/
	FILE *salida;
	salida = fopen ( archivo_salida, "w" ); /* Como el optimo es el primero, hago que sobreescriba la salida */
	fputs("Algoritmo OPTIMO\n\n", salida);

	/* inicio las variables que voy a necesitar */
	int cantidad_marcos = largo_lista(aux);
	int dato_actual;
	int m = 0;
	int hits = 0;
	int miss = 0;
	int big;
	char cadena[1000];
	int k;

	int futuro[cantidad_marcos];
	int antiguedad[cantidad_marcos];
	for(i = 0; i < cantidad_marcos; i++)
	{
		futuro[i] = 0;
		antiguedad[i] = 0;
	}

	for(i = 0; i < cantidad_entrada; i++)
	{
		dato_actual = datos[i];

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
			fputc('\n', salida);

			//aumento la antiguedad de una pagina en caso de que exista
			for(j = 0; j < cantidad_marcos; j++)
			{
				if(recuperar_dato(0,aux) != -10000)
				{
					antiguedad[j]++;
				}
			}

			antiguedad[posicion(dato_actual,aux)] = 0;

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
					futuro[j] = mirar_futuro(i, cantidad_entrada, datos, recuperar_dato(j,aux));
				}
				big = mayor(futuro, cantidad_marcos);
				insertar_dato(dato_actual, big, aux);

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

			//aumento la antiguedad de una pagina en caso de que exista
			for(j = 0; j < cantidad_marcos; j++)
			{
				if(recuperar_dato(0,aux) != -10000)
				{
					antiguedad[j]++;
				}
			}
		}
	}

	float tasa_miss = ((float)miss/(float)(miss + hits)) * 100;
	float tasa_hits = ((float)hits/(float)(miss + hits)) * 100;

	sprintf(cadena, "%5.2f%c\n\n", tasa_miss,37);
	fputs(cadena,salida);

	sprintf(cadena, "%5.2f%c\n", tasa_hits,37);
	fputs(cadena,salida);

	fclose(entrada);
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