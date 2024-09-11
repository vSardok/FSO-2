/*
 * Para compilar hay que agregar la librería matemática
 *  	gcc -o  .c -lm
 *		gcc -o  .c -lm -lpthread
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>


#define INTERVALOS 1000000000 // Dividir el intervalo (0 - 1) en N rectangulos
#define NTHREADS 4
double SIZE;
double PI;

double funcion(double x){ // funcion = sqrt(1-y^2)
    return sqrt(1.0-x*x);
}

// double get_pi(double SIZE){
//     double sum=0.0;
//     for (double y = 0; y < 1; y+=SIZE)  // Por cada intervalo
//     {
//         sum+=funcion(y);    //  Sumar la altura del rectangulo mediante la formula f(x) = sqrt(1-y^2)
//     }
//     return sum*4*SIZE; // Debido a que eso es 1/4 del circulo, se multiplica por 4, ademas, como la base es siempre la misma, en lugar de multiplicarla en cada iteracion, mejor 1 vez al final
// }

void *tfunc(void *args)
{
    int tnum = *((int *)args);
    double start = (double)tnum/NTHREADS;
    double end = (double)(tnum+1)/NTHREADS;
    double sum=0.0;
    // printf("Thread: %d:\nStart %.2f\nEnd %.2f\n", tnum, start, end);
    for (double y = start; y < end; y+=SIZE)  // Por cada intervalo
    {
        sum+=funcion(y);    //  Sumar la altura del rectangulo mediante la formula f(x) = sqrt(1-y^2)
    }
    PI+=sum; // Agregar la porcion calculada por el hilo al cumulo de pi
}


int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
    struct timeval ts;
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial
    SIZE = 1.0/INTERVALOS;

    // Calcular pi con la regla del trapecio
    // pi = get_pi(1.0/INTERVALOS);
    int i;
    pthread_t tid[NTHREADS];
    int params[NTHREADS];

	for(i=0;i<NTHREADS;i++)
    {
        params[i] = i;
        pthread_create(&tid[i],NULL,tfunc,&params[i]);
    }

	for(i=0;i<NTHREADS;i++)
        pthread_join(tid[i],NULL);

    PI*=4*SIZE; // Debido a que eso es 1/4 del circulo, se multiplica por 4, ademas, como la base es siempre la misma, en lugar de multiplicarla en cada iteracion, mejor 1 vez al final
    printf("Pi %.8f",PI);

	// Hasta aquí termina lo que se tiene que hacer en paralelo
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
	elapsed_time = stop_ts - start_ts;
	printf("\n------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}