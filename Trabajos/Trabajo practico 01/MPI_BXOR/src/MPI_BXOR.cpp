/*
 ============================================================================
 Name        : MPI_BXOR.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : MPI_BXOR
 ============================================================================
 */

#include <math.h> 
#include "mpi.h" 
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	int rank;
	int resBXOR = 0;
	int nroBit;

	/* Iniciamos MPI */
	MPI_Init(NULL, NULL);

	/* Seleccionamos el rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printf("Antes de aplicar MPI_Reduce\n");
		printf("BXOR es: %d\n", resBXOR);

	}

	switch (rank) {
	case 0:
		nroBit = 1;
		break;
	case 1:
		nroBit = 0;
		break;
	case 2:
		nroBit = 0;
		break;
	default:
		break;
	}

	MPI_Reduce(&nroBit, &resBXOR, 1, MPI_INT, MPI_BXOR, 0, MPI_COMM_WORLD);

	if (rank == 0) {

		printf("Luego de aplicar MPI_Reduce BXOR %d\n", resBXOR);

	}
	/* Finaliza MPI */
	MPI_Finalize();

	return 0;
}
