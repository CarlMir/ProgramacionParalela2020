#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global variable: */
int thread_count;
int res=1;
int n;

/* Thread function */
void* factorial(void* rank);

int main(int argc, char* argv[]) {

	long thread; /* Use long in case of a 64 − bit system */
	pthread_t* thread_handles;

	/* Get number of threads from command line */
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));

	printf("Ingrese el Factorial que desee hallar: ");
	scanf("%d",&n);

	for (thread = 0; thread < thread_count; thread++){
		pthread_create(		&thread_handles[thread], //Arreglo de punteros de ID de los hilos
							NULL, //Null por defecto
							factorial, //Funcion a correr por el hilo
							(void*) thread	); //Argumento de la Funcion que debe retornar un void
	}

	//Une a los threads
	for (thread = 0; thread < thread_count; thread++){
		pthread_join(	thread_handles[thread],
						NULL	);
	}

	printf("El resultado del factorial es: %d",res);


	free(thread_handles); //libera memoria de array de punteros de los hilos
	return 0;
}/* main */

void* factorial(void* rank) {

	int my_rank= (long) rank;
	int data = my_rank + 1;

	do {
		res = res * data;
		data = data + thread_count;

	} while (data <= n);


	return NULL;
}/* Hello */
