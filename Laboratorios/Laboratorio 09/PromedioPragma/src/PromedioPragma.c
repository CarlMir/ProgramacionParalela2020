/*
 ============================================================================
 Name        : PromedioPragma.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int lista[] = { 2, 4, 6, 8 };
int suma;
double promedio;

int main(int argc, char *argv[]) {

	int numThreads, tid;

	/* This creates a team of threads; each thread has own copy of variables  */
	#pragma omp parallel private(numThreads, tid)
	{
		tid = omp_get_thread_num();
		printf("Hello World from thread number %d\n", tid);

		/* The following is executed by the master thread only (tid=0) */
		numThreads = omp_get_num_threads();
		if (tid == 0) {
			for(int i = 0; i<2;i++){
				suma+=lista[i];
			}
			promedio = suma/2;
		} else {
			for(int i = 0; i<2;i++){
				suma+=lista[i];
			}
			promedio = suma/2;
		}

		printf("El promedio es: %f\n", promedio);
	}
	return 0;
}

