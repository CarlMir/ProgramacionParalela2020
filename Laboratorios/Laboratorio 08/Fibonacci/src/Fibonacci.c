/*
 ============================================================================
 Name        : Fibonacci.c
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

void* fibonacci(void *rank);

/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main (int argc, char *argv[]) {

	long thread;
	pthread_t *thread_handles;

	if (argc != 2)
		exit(0);

	thread_count = atoi(argv[1]);

	thread_handles = malloc(thread_count * sizeof(pthread_t));

	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, fibonacci, (void*) thread+1);

	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	printf("El fibonacci de %d es: %d\n", thread_count,resultado);

	return 0;
}

void* fibonacci(void *rank){

	long my_rank = (long)rank;

	printf("\n%d", my_rank);

	return NULL;
}
