/*
 ============================================================================
 Name        : SumaDeVectores2.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : SumaVectores2 -intento
 ============================================================================
 */

#include <math.h>
#include "mpi.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

void f1(int result[], int recibido[], int rango_ini, int rango_fin) {
	int i;
	for (i = rango_ini; i <= rango_fin; i++) {
		result[i] = recibido[i];
	}
}

int main(int argc, char *argv[]) {
	int rank, i;
	int arr1[100], arr2[100], arrResult[100];

	for (int i = 0; i < 100; i++) {
		arr1[i] = rand() % 100;
		arr2[i] = rand() % 100;
	}

	MPI::Init(argc, argv);
	rank = MPI::COMM_WORLD.Get_rank();
	MPI_Status estado;

	int rango_ini = (rank) * 10;
	int rango_fin = (rank + 1) * 10 - 1;
	for (i = rango_ini; i <= rango_fin; i++) {
		arrResult[i] = arr1[i] + arr2[i];
	}

	if (rank != 0) {
		MPI_Send(&arrResult, rank, MPI_INT, 0, 0, MPI_COMM_WORLD);
	} else {
		int arrRecibido[10];

		for (int k = 1; k <= 9; k++) {
			MPI_Recv(&arrRecibido, 100, MPI_INT, k, 0, MPI_COMM_WORLD, &estado);
			f1(arrResult, arrRecibido, k * 10, (k * 10) + 9);
		}

		for (int i = 0; i < 100; i++) {
			cout << "Indice " << i << " \t" << arrResult[i] << endl;
		}
	}

	MPI::Finalize();
	return 0;
}
