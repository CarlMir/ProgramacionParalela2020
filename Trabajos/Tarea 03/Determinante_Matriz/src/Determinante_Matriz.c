/*
 ============================================================================
 Name        : Determinante_Matriz.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C

 Compilar: gcc -g -Wall -fopenmp det Determinante_Matriz.c -lm
 Ejecutar: ./det
 como pow se encuentra en math.h y estamos compilando con gcc
 se añade al final -lm.
 ============================================================================
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX 10

void mostrar_matriz(int matriz[][MAX], int orden);
int determinante(int matriz[][MAX], int orden);
int cofactor(int matriz[][MAX], int orden, int fila, int columna);

int main() {
	int matriz[MAX][MAX];
	int orden, i, j;
	int matrizResul;

	printf("Ingresa el orden de la matriz (maximo %d): ", MAX);
	scanf("%d", &orden);
	while (orden < 0 || orden > MAX) {
		printf("\nEl orden de la matriz no puede ser mayor que %d\n", MAX);
		printf("Ingrese nuevamente el orden de la matriz: ");
		scanf("%d", &orden);
	}

	/* Se generan los elementos de la matriz de manera aleatoria */
	srand(time(NULL));
	for (i = 0; i < orden; i++) {
		for (j = 0; j < orden; j++) {
			matriz[i][j] = rand() % 10;
		}
	}

	printf("\nMatriz generada aleatoriamente de orden %d:\n\n", orden);
	mostrar_matriz(matriz, orden);

	#pragma omp parallel
	{
		matrizResul = determinante(matriz, orden);
	}

	printf("\nEl determinante de la matriz es: %d\n", matrizResul);

	return 0;
}

void mostrar_matriz(int matriz[][MAX], int orden) {
	int i, j;

	for (i = 0; i < orden; i++) {
		for (j = 0; j < orden; j++) {
			printf("\t%d", matriz[i][j]);
		}
		printf("\n");
	}
}

int determinante(int matriz[][MAX], int orden) {
	int det = 0.0, j;

	if (orden == 1) {
		det = matriz[0][0];
	} else {
		for (j = 0; j < orden; j++) {
			det = det + matriz[0][j] * cofactor(matriz, orden, 0, j);
		}
	}

	return det;
}

int cofactor(int matriz[][MAX], int orden, int fila, int columna) {
	int submatriz[MAX][MAX];
	int n = orden - 1;
	int i, j;

	int x = 0;
	int y = 0;
	for (i = 0; i < orden; i++) {
		for (j = 0; j < orden; j++) {
			if (i != fila && j != columna) {
				submatriz[x][y] = matriz[i][j];
				y++;
				if (y >= n) {
					x++;
					y = 0;
				}
			}
		}
	}

	return pow(-1.0, fila + columna) * determinante(submatriz, n);
}
