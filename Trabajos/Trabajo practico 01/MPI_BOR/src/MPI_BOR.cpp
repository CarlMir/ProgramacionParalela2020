/*
 ============================================================================
 Name        : MPI_BOR.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : MPI_BOR
 ============================================================================
 */

#include <math.h> 
#include "mpi.h" 
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	int rank;
	int resBOR = 0;
	int nroBit;

	/* Iniciamos MPI */
	MPI_Init(NULL, NULL);

	/* Elegimos el rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printf("Antes de aplicar MPI_Reduce %d\n", resBOR);

	}

	switch (rank) {
	case 0:
		nroBit = 0;
		break;
	case 1:
		nroBit = 1;
		break;
	case 2:
		nroBit = 0;
		break;
	default:
		break;
	}

	MPI_Reduce(&nroBit, &resBOR, 1, MPI_INT, MPI_BOR, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Luego de aplicar MPI_Reduce BOR %d\n", resBOR);

	}
	/* Finaliza MPI */
	MPI_Finalize();

	return 0;

}

