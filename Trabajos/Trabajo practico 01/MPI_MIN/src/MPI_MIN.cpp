/*
 ============================================================================
 Name        : MPI_MIN.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : MPI_MIN
 ============================================================================
 */

#include <math.h> 
#include <stdio.h>
#include "mpi.h" 
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	int rank;
	int Data = 0;
	int minData = 0;

	/* Inicializamos MPI */
	MPI_Init(NULL, NULL);

	/* Seleccionamos el rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	Data = (rank + 1) * 4;

	if (rank == 0) {
		cout << "Antes de aplicar MPI_Reduce" << endl;
		cout << "El min es: " << minData << endl;
	}

	MPI_Reduce(&Data, &minData, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		cout << "Despues de aplicar MPI_Reduce" << endl;
		cout << "El min numero de todos los procesos es: " << minData << endl;
	}
	MPI_Finalize();

	return 0;
}

