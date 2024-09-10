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
//#include <pthread.h>


#define INTERVALOS 100
#define THREADS 4
double interval_SIZE;

double funcion(double x){
    return sqrt(1.0-x*x);
}

double get_pi(double size){
    double sum=0.0;
    for (int i = 0; i < size; i++)
    {
        sum+=funcion(interval_SIZE*i);
    }
    return sum*4*interval_SIZE;
}

// void *tfunc(void *args)
// {
//     int i,j,k;
//     int num = *((int *)args);
//     int start = num * (SIZE/THREADS);
//     int end = (num+1) * (SIZE/THREADS);
// }


int main()
{
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
    struct timeval ts;
    double pi;
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    interval_SIZE = 1.0/ INTERVALOS;
    pi = get_pi(INTERVALOS);
    printf("Pi %f",pi);

	// for(i=0;i<THREADS;i++)
    // {
    //     param[i] = i;
         //pthread_create(&IDs[i],NULL,tfunc,&param[i]);
    // }

	// for(i=0;i<THREADS;i++)
    //     pthread_join(IDs[i],NULL);

	// Hasta aquí termina lo que se tiene que hacer en paralelo
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
	elapsed_time = stop_ts - start_ts;


	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %lld segundos\n",elapsed_time);
}