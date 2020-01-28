/*
 ============================================================================
 Name        : MPI_BAND.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : MPI_BAND
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	int rank;
	int resBAND = 0;
	int nroBit;

	/* Iniciamos MPI */
	MPI_Init(NULL, NULL);

	/* Seleccionamos el rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printf("Antes de aplicar MPI_Reduce ");
		printf("BAND es: %d\n", resBAND);

	}

	switch (rank) {
	case 0:
		nroBit = 101;
		break;
	case 1:
		nroBit = 001;
		break;
	case 2:
		nroBit = 101;
		break;
	default:
		break;
	}

	MPI_Reduce(&nroBit, &resBAND, 1, MPI_INT, MPI_BAND, 0, MPI_COMM_WORLD);

	if (rank == 0) {

		if (resBAND == 1) {
			printf("AND en binario es: 00%d\n", resBAND);
		} else if (resBAND == 10) {
			printf("AND en binario es: 0%d\n", resBAND);
		} else if (resBAND == 0) {
			printf("AND en binario es: 00%d\n", resBAND);
		} else {
			printf("Luego de aplicar MPI_Reduce %d\n", resBAND);
		}

	}
	MPI_Finalize();

	return 0;
}
