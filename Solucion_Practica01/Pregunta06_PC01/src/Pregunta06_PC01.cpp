/*
 ==============================================================================================
 Name        : Pregunta06_PC01.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description :
 La pregunta 06 consiste en saber cuantas veces se repite un numero en un vector A[].
 En este caso usaremos 4 procesos y un vector A[] de 20 elemento definidos de manera aleatoria.
 El numero que encontraremos lo definimos en la variable encontrar
 ==============================================================================================
 */

#include <math.h>
#include <iostream>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) {

	int comm_sz, rank, contador = 0, iguales, encontrar = 0;
	int A[20] = { 0 };
	int B[5] = { 0 };

	MPI_Comm comm;

	MPI_Init(&argc, &argv);
	comm = MPI_COMM_WORLD;
	MPI_Comm_size(comm, &comm_sz);
	MPI_Comm_rank(comm, &rank);

	if (rank == 0) {

		srand(time(NULL));
		for (unsigned int x = 0; x < sizeof(A) / sizeof(A[0]); x++) {
			A[x] = rand() % 10;
			if (x == 0)
				cout << "vector A[ ";
			cout << A[x] << " ";
			if (x == (sizeof(A) / sizeof(A[0])) - 1)
				cout << "]" << endl;
			else
				cout << ", ";
		}
		printf("Digite el numero que desea saber cuantas veces se encuentra en el arreglo:\n");
		scanf("%d", &encontrar);
	}

	/* Repartimos a todos los procesos el valor que queremos encontrar */
	MPI_Bcast(&encontrar, 1, MPI_INT, 0, comm);

	/* Se reparten el vector de manera equitativa entre los 4 procesos */
	MPI_Scatter(&A, 5, MPI_INT, &B, 5, MPI_INT, 0, comm);

	/* Que proceso tiene que sub-vector */
	cout << "Proceso: " << rank << " -> ";
	for (int i = 0; i < 5; i++) {
		if (i == 0)
			cout << "[ ";
		cout << B[i] << " ";
		if (i == 5 - 1)
			cout << "]";
		else
			cout << ", ";
	}
	cout << " -> ";

	/* Comparamos los elementos
	 * del vector con el numero
	 * que deseamos saber cuantas veces se repite*/
	for (int j = 0; j < 5; j++) {
		if (B[j] == encontrar)
			contador++;
	}

	cout << "El numero " << encontrar << " aparece " << contador << endl;

	/* Reduccion */
	MPI_Reduce(&contador, &iguales, 1, MPI_INT, MPI_SUM, 0, comm);

	if (rank == 0) {
		/* Mostramos la cantidad de veces que aparece el valor de "encontrar" en el vector */
		cout << "La cantidad total de veces que aparece el numero " << encontrar << " es: " << iguales << endl;
	}

	MPI_Finalize();

	return 0;
}

