/*
 ============================================================================
 Name        : MPI_MAX.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : MPI_MAX
 ============================================================================
 */

#include <math.h>
#include <stdio.h>
#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	int rank;
	int actual = 0;
	int miMax = 0;

	/* Inicializamos MPI */
	MPI_Init(NULL, NULL);

	/* Seleccionamos el rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	actual = (rank + 1) * 8;

	if (rank == 0) {
		cout << "Antes de aplicar MPI_Reduce" << endl;
		cout << "El max es: " << miMax << endl;
	}

	MPI_Reduce(&actual, &miMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		cout << "Despues de aplicar MPI_Reduce" << endl;
		cout << "El max numero de todos los procesos es: " << miMax << endl;
	}
	MPI_Finalize();

	return 0;
}
