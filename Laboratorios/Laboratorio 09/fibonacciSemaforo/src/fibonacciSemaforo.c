/*
 ============================================================================
 Name        : fibonacciSemaforo.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

const int MAX_THREADS = 1024;
const int MSG_MAX = 100;

int thread_count;
int **messages;
sem_t *semaphores;


int thread_count;
int cantidad;
int fibonacci = 0;
int numero[] = { 1, 1 };

int fibo[] = { 1, 1 };
int suma = 0;

void Usage(char *prog_name);
void* fiboSemaforo(void *rank);

int main(int argc, char *argv[]) {
	long thread;
	pthread_t *thread_handles;
	printf("Digite un numero: ");
	scanf("%d", &cantidad);

	if (argc != 2)
		Usage(argv[0]);
	thread_count = strtol(argv[1], NULL, 10);
	if (thread_count <= 0 || thread_count > MAX_THREADS)
		Usage(argv[0]);

	thread_handles = malloc(thread_count * sizeof(pthread_t));
	messages = malloc(thread_count * sizeof(int*));
	semaphores = malloc(thread_count * sizeof(sem_t));
	for (thread = 0; thread < thread_count; thread++) {
		messages[thread] = NULL;
		/* Initialize all semaphores to 0 -- i.e., locked */
		sem_init(&semaphores[thread], 0, 0);
	}

	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], (pthread_attr_t*) NULL, fiboSemaforo, (void*) thread);

	for (thread = 0; thread < thread_count; thread++) {
		pthread_join(thread_handles[thread], NULL);
	}

	for (thread = 0; thread < thread_count; thread++) {
		free(messages[thread]);
		sem_destroy(&semaphores[thread]);
	}
	free(messages);
	free(semaphores);
	free(thread_handles);


	printf("Resultado: %d \n", fibonacci);

	return 0;
}

void* fiboSemaforo(void *rank) {
	long my_rank = (long) rank;
	long dest = (my_rank + 1) % thread_count;
	int local_m = cantidad / thread_count;
	int inicio = my_rank * local_m + 1;
	int fin = (my_rank + 1) * local_m;

	for (int i = inicio; i < fin; i++) {
		suma = numero[0] + numero[1];
		fibonacci = suma;
		numero[0] = numero[1];
		numero[1] = suma;
	}

	printf("valor %d %ld %ld\n", suma, my_rank, dest);
	sem_post(&semaphores[dest]); /* "Unlock" the semaphore of dest */

	sem_wait(&semaphores[my_rank]); /* Wait for our semaphore to be unlocked */


	return NULL;
}

void Usage(char *prog_name) {

	fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
	exit(0);
} /* Usage */

