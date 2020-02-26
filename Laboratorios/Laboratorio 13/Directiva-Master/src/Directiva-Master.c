/*
 ============================================================================
 Name        : Directiva-Master.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {
	int a[5], i;

	#pragma omp parallel
	{
		// Perform some computation.
		#pragma omp for
		for (i = 0; i < 5; i++)
			a[i] = i * i;

		// Print intermediate results.
		#pragma omp master
		for (i = 0; i < 5; i++)
			printf("a[%d] = %d\n", i, a[i]);

		// Wait.
		#pragma omp barrier

		// Continue with the computation.
		#pragma omp for
		for (i = 0; i < 5; i++)
			a[i] += i;
	}
	return 0;
}

