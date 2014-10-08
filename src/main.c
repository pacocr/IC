/*
 * Pr�cticas 1 y 2 IC
 * Problema de los N cuerpos.
 * Lenguaje: C
 */


#include <stdio.h>
#include <stdlib.h>

#include "coordenadas.h"
#include "gravedad.h"
#include "fichero.h"
#include "interfaz.h"
#include "cuerpo.h"


typedef struct
{
	float velocidad; //Velocidad inicial
	int numeroCuerpos; //N�mero de cuerpos
	int numeroMovimientos; //N�mero de movimientos de los cuerpos
	TCuerpo* cuerpos; //Posiciones de los cuerpos
	TGravedad gravedad; //Punto de gravedad

}TParametros;



void rellenar_parametros(TParametros*);
void ejecutar(TParametros*);
void liberar(TParametros*);
void imprimir_parametros(TParametros*);



/*
 * Funci�n principal
 */
int main(int argc, char *argv[]){

	TParametros param;
	rellenar_parametros(&param);



	ejecutar(&param);


	//TODO Imprime los par�metros iniciales para comprobar que funciona bien
	imprimir_parametros(&param);




	liberar(&param); //Libera memoria din�mica de par�metros

	return 0;
}



/*
 * Ejecuci�n principal del programa
 */
void ejecutar(TParametros* param)
{
	char* linea = ""; //Texto de prueba
	FILE* fichero;
	fichero = fopen ( "posiciones.txt", "w");





	int i,c;
	for(i=0; i<param->numeroMovimientos;i++)
	{
		for (c=0; c<param->numeroCuerpos; c++){
			aplicar_gravedad(&(param->cuerpos[c]), &(param->gravedad));
			linea = imprimir(&(param->cuerpos[c]));

			guardar_en_fichero(fichero,linea);
			guardar_en_fichero(fichero,"\n");
		}

	}





	fclose(fichero);
}




void imprimir_parametros(TParametros* param)
{
	int i;
	printf("\nDatos:\n");
	printf("La velocidad es: %f\n",param->velocidad);
	printf("El numero de cuerpos es: %d\n",param->numeroCuerpos);
	printf("Posicion de los cuerpos:\n");
	for(i=0;i<param->numeroCuerpos;i++)
	{
		printf("\tCuerpo %d: %d , %d\n",i, param->cuerpos[i].posicion.x, param->cuerpos[i].posicion.y);
	}
	printf("El numero de movimientos es: %d\n", param->numeroMovimientos);
	printf("La fuerza de gravedad es: %f\n", param->gravedad.fuerza);
}





/*
 * Libera memoria din�mica (cuerpos)
 */
void liberar(TParametros* param)
{
	free(param->cuerpos); //Libera memoria din�mica
}






/**
 * Rellena los par�metros necesarios para la ejecuci�n del programa
 */
void rellenar_parametros(TParametros* param)
{
	int numeroCuerpos, numeroMovimientos, i, pos_mayor=1;
	float velocidad;
	TGravedad gravedad;
	TCuerpo* cuerpos;
	TCuerpo cuerpo;


	//N�mero de cuerpos
	numeroCuerpos = numero_cuerpos();

	//Array din�mico de posiciones de los cuerpos
	cuerpos = (TCuerpo *)malloc (numeroCuerpos * sizeof(TCuerpo));

	//Establecer posici�n de cada cuerpo
	for(i=0; i<numeroCuerpos; i++)
	{
		cuerpo.posicion = coordenada_cuerpo(i);
		if(pos_mayor < abs(cuerpo.posicion.x))
			pos_mayor = abs(cuerpo.posicion.x);
		cuerpos[i]=cuerpo;
	}

	//Velocidad inicial
	velocidad = velocidad_inicial();


	//N�mero de iteraciones
	numeroMovimientos = numero_movimientos();


	//Fuerza de gravedad
	gravedad.fuerza = fuerza_gravedad();
	gravedad.posicion.y = pos_mayor*10;
	gravedad.posicion.x = pos_mayor*10;


	//Vuelca los valores en la estructura de tipo TParametros.
	param->numeroCuerpos = numeroCuerpos;
	param->velocidad = velocidad;
	param->cuerpos = cuerpos;
	param->numeroMovimientos = numeroMovimientos;
	param->gravedad = gravedad;

}
