/*
 ============================================================================
 Name        : Pregunta07_PC01.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description :
 Con este programa calcularemos el factorial de un numero menor o igual
 12.
 la cantidad de procesos debe ser menor que 12.
 ============================================================================
 */

#include <math.h>
#include <iostream>
#include <vector>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) {

	int comm_sz, rank, num = 0, prod_local = 0, factorial = 0;
	int numPro = 0;
	int A[num] = { 0 };
	int B[numPro] = { 0 };

	MPI_Comm comm;

	MPI_Init(&argc, &argv);
	comm = MPI_COMM_WORLD;
	MPI_Comm_size(comm, &comm_sz);
	MPI_Comm_rank(comm, &rank);
	if (rank == 0) {
		/* Ingresamos el numero del cual queremos su factorial */
		printf("Digite el numero del que quiere hallar su factorial:\n");
		scanf("%d", &num);
		numPro = (num / comm_sz);
		for (int x = 0; x < num; x++) {
			A[x] = x + 1;
		}
	}

	/* Repartimos a todos los procesos el valor que queremos encontrar */
	MPI_Bcast(&num, 1, MPI_INT, 0, comm);
	MPI_Bcast(&numPro, 1, MPI_INT, 0, comm);

	/* Se reparten el vector de manera equitativa entre los 4 procesos */
	MPI_Scatter(&A[0], numPro, MPI_INT, &B[0], numPro, MPI_INT, 0, comm);

	/* Que proceso tiene que sub-vector */
	cout << "Proceso: " << rank << " -> ";
	for (int i = 0; i < numPro; i++) {
		if (i == 0)
			cout << "[ ";
		cout << B[i] << " ";
		if (i == numPro - 1)
			cout << "]";
		else
			cout << ", ";
	}
	cout << " -> ";

	/* Hacemos el productor del factorial */
	for (int j = 0; j < numPro; j++) {
		if (j == 0) {
			prod_local = B[0];
		} else {
			prod_local = prod_local * B[j];
		}
	}

	cout << "Producto de parcial: " << prod_local << endl;

	/* Reduccion */
	MPI_Reduce(&prod_local, &factorial, 1, MPI_INT, MPI_PROD, 0, comm);

	if (rank == 0) {
		/* Mostramos el factorial del numero */
		cout << "El factorial del numero " << num << " es: " << factorial << endl;
	} else {

	}

	MPI_Finalize();

	return 0;
}
