/**
* @file fechas.c
* @version 1.1
* @Author Oscar Unzueta
* @date 6/10/2020
* @brief Correción de las fechas en tablas del LIMS a partir del fichero REPORTER_SAMPLE-CSV exportado en CSV separado por comas
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 724


int main(int argc, char *argv[]) {
	
	char * cadena;	    
	char *a;
	char * token;
	char ruta[25];
	int largo=0,lineas=0,lineasCorregidas=0,deteccion,i,aux,cmd=0;
	FILE *original, *corregido;
	
	if((  cadena = (char*)malloc ( MAX*sizeof(char) )   ) == NULL) {
        return -1;
    }
	
	printf("Ayuntamiento de Vitoria, Laboratorio Municipal\n ");
	printf("Procesando el fichero REPORTER_SAMPLE.CSV\n ");
	
	if (argc>1) {
		    cmd=1;
			printf(">>>>>>>Abriendo archivo %s\n",argv[1]);
			original=fopen(argv[1],"r");	
	}else {
		original=fopen("REPORTER_SAMPLE.CSV","r");			
	}
	
	// calculo de la longitud de la linea
	for (i=0;i<2;i++){ 
	    fgets(cadena,MAX,original);
    	aux = strlen(cadena);
    	if (aux>largo) largo=aux;	
    }	

	printf("El largo de la linea es %d caracteres. Los campos son los siguientes:\n\a",largo);
	
	// funcion split para separar por comas	
	token=strtok(cadena,",");
	if (token !=NULL){
		while (token !=NULL){
			printf("%s\n",token);
				token=strtok(NULL,",");
		}
	} 
 

	fclose(original);
	
	if (cmd==1){
		original=fopen(argv[1],"r");
	}else{
		original=fopen("REPORTER_SAMPLE.CSV","r");
	}
	
	//cadena = (char*)malloc ( largo*sizeof(char) );
	cadena=realloc(cadena,largo*sizeof(char));
	
	corregido=fopen("REPORTER_SAMPLE_corregido.CSV","w");
		
	if (original==NULL){
		printf("Error al abrir el fichero.\n  Hay que utilizar el formato E:\\nombre\\nombre\n\a");
		printf("Introduce la ruta al archivo ");
		scanf("%c",&ruta);
		original=fopen(ruta,"r");		
	}
	
   while( !feof(original) ) {
    	lineas++;
	    fgets(cadena,MAX,original);
        printf("-"); 

		do {   // detecta si la fecha esta en ingles y lo pasa a castellano
		   	a=NULL;
			deteccion=0;
			a=strstr(cadena,"-DEC-");
				if (a!=NULL){
					lineasCorregidas++;
					deteccion++;
					*(a+2)='I';
					printf("*");
					a=NULL;
					}
			a=strstr(cadena,"-APR-");
				if (a!=NULL){
					lineasCorregidas++;
					deteccion++;
					*(a+2)='B';
					printf("*");
					a=NULL;
					}				
			a=strstr(cadena,"-AUG-");
				if (a!=NULL){
					lineasCorregidas++;
					deteccion++;
					*(a+1)='A';
					*(a+2)='G';
					*(a+3)='O';
					printf("*");
					a=NULL;
					}		
			a=strstr(cadena,"-JAN-");
				if (a!=NULL){
					lineasCorregidas++;
					deteccion++;
					*(a+1)='E';
					*(a+2)='N';
					*(a+3)='E';
					printf("*");
					a=NULL;
					}								
		} while(deteccion!=0);     // end of detection
	    a=NULL;
		fprintf(corregido,"%s",cadena);	
    }  // end of while eof

	fclose(original);

	if (fclose(corregido)==0){
		printf("\nSe cerro el fichero correctamente.\n");
		printf("Se procesaron %d lineas.\n",lineas);
		printf("Se corrigieron %d fechas.\n",lineasCorregidas);
	   	printf("Ayuntamiento de Vitoria, Laboratorio Municipal\n ");
	}
	free(cadena);
	return 0;
} // end of main
