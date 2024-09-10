/*
 * Para compilar hay que agregar la librería matemática
 *  	gcc -o  .c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#define INTERVALOS 1000000000 // Dividir el intervalo (0 - 1) en N rectangulos

double funcion(double x){ // funcion = sqrt(1-y^2)
    return sqrt(1.0-x*x);
}

double get_pi(double size){
    double sum=0.0;
    for (double y = 0; y < 1; y+=size)  // Por cada intervalo
    {
        sum+=funcion(y);    //  Sumar la altura del rectangulo mediante la formula f(x) = sqrt(1-y^2)
    }
    return sum*4*size; // Debido a que eso es 1/4 del circulo, se multiplica por 4, ademas, como la base es siempre la misma, en lugar de multiplicarla en cada iteracion, mejor 1 vez al final
}

int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
    struct timeval ts;
    double pi;
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial
    
    // Calcular pi con la regla del trapecio
    pi = get_pi(1.0/INTERVALOS);
    printf("Pi %.15f",pi);

	// Hasta aquí termina lo que se tiene que hacer en paralelo
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
	elapsed_time = stop_ts - start_ts;
	printf("\n------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}