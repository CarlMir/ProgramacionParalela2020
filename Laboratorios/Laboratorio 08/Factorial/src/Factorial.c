/*
 ============================================================================
 Name        : Factorial.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int n, resultado = 1;

void* factorial(void *rank);

/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {

	long thread;
	pthread_t *thread_handles;

	if (argc != 2)
		exit(0);

	thread_count = atoi(argv[1]);

	printf("Ingrese el numero:\n");
	scanf("%d", &n);

	thread_handles = malloc(thread_count * sizeof(pthread_t));

	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, factorial, (void*) thread);

	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	printf("El factorial de %d es: %d\n", n, resultado);

	return 0;
}

void* factorial(void *rank) {

	long my_rank = (long) rank;
	int i;


	if(n % thread_count == 0){
		int local = n / thread_count;
		int first = my_rank * local + 1;
		int last = (my_rank + 1) * local;
		printf("local %d\n", local);
		printf("1 %d\n", first);
		printf("2 %d\n", last);
		for (i = first; i <= last; i++) {
			resultado *= (i);
			printf("resul par: %d es %ld es %d\n", i, my_rank, resultado);
		}
	}else{
		int local = (n / thread_count) + 1;
		int first = my_rank * local + 1;
		int last = (my_rank + 1) * local;
		printf("local %d\n", local);
		printf("1 %d\n", first);
		printf("2 %d\n", last);
		for (i = first; i <= last; i++) {
			resultado *= (i);
			printf("resul impar: %d es %ld es %d\n", i, my_rank, resultado);
		}
	}

	return NULL;
}

