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

int optimo(lista *L, char *archivo_entrada, char *archivo_salida)
{

	/* abro el archivo de entrada */
	FILE *fp;
	fp = fopen ( archivo_entrada, "r" );        
	if (fp==NULL) 
	{
		printf("Archivo de entrada no existe\n"); 
		exit (1);
	}
	

	return 0;
}