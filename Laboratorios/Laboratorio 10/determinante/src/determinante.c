#include <stdio.h>
#include <math.h>
#define MAX 20

void mostrar_matriz(int matriz[][MAX], int orden);
int determinante(int matriz[][MAX], int orden);
double cofactor(int matriz[][MAX], int orden, double fila, double columna);

int main() {

	int matriz[MAX][MAX];

	int orden, i, j;

	printf("Ingresa el orden de la matriz (maximo %d): ", MAX);

	scanf("%d", &orden);

	while (orden < 0 || orden > MAX) {

		printf("\nEl orden de la matriz no puede ser mayor que %d\n", MAX);

		printf("Ingrese nuevamente el orden de la matriz: ");

		scanf("%d", &orden);

	}

	printf("\nIngrese los elementos de la matriz:\n\n");

	for (i = 0; i < orden; i++) {

		for (j = 0; j < orden; j++) {

			scanf("%d", &matriz[i][j]);

		}

	}

	printf("\nMostrando la matriz ingresada:\n");

	mostrar_matriz(matriz, orden);

	printf("\nEl determinante es: %d\n", determinante(matriz, orden));

	getchar();

	getchar();

	return 0;

}

void mostrar_matriz(int matriz[][MAX], int orden) {

	int i, j;

	printf("Orden: %d\n", orden);

	for (i = 0; i < orden; i++) {

		for (j = 0; j < orden; j++) {

			printf("\t%d", matriz[i][j]);

		}

		printf("\n");

	}

}

int determinante(int matriz[][MAX], int orden) {

	int det = 0.0, j, i;
	int prod = 1;

	if (orden == 1) {

		det = matriz[0][0];

	} else {

		for (j = 0; j < orden; j++) {
			int posicion = j;
			int numero = matriz[0][posicion];
			prod *= numero;

			for(int i = 1; i < orden; i++){
				posicion++;
				if(j+i > orden) posicion = 0;
				numero = matriz[0][posicion];
				prod *= numero;
			}

			det += prod;
			prod = 1;


			//for (i = 0; i < orden; i++) {
			//	if(j>i){
			//		j = 0;
			//	}
			//	prod *= matriz[i][j];
			//}
//			det = det + matriz[0j][j] * cofactor(matriz, orden, 0, j);

		}
		for (j = orden; j < 0; j--) {
			int posicion = j;
			int numero = matriz[0][j];
			prod *= numero;

			for(int i = orden; i < orden; i++){
				posicion--;
				if(j+i > orden) posicion = 0;
				numero = matriz[0][posicion];
				prod *= numero;
			}
			if(j-1 == 0) j = orden;
			numero = matriz[0][j-2];
			prod *= numero;

			det -= prod;
			prod = 1;

					//for (i = 0; i < orden; i++) {
					//	if(j>i){
					//		j = 0;
					//	}
					//	prod *= matriz[i][j];
					//}
		//			det = det + matriz[0j][j] * cofactor(matriz, orden, 0, j);

				}

//		det += prod;

	}

	return det;

}

//int cofactor(int matriz[][MAX], int orden, int fila, int columna) {
//
//	int submatriz[MAX][MAX];
//
//	int n = orden - 1;
//
//	int i, j;
//
//	int x = 0;
//
//	int y = 0;
//
//	for (i = 0; i < orden; i++) {
//
//		for (j = 0; j < orden; j++) {
//
//			if (i != fila && j != columna) {
//
//				submatriz[x][y] = matriz[i][j];
//
//				y++;
//
//				if (y >= n) {
//
//					x++;
//
//					y = 0;
//
//				}
//
//			}
//
//		}
//
//	}
//	double suma = (fila + columna);
//	//double potencia = pow(-1.0, 3.0);
//
//	int factor = -1;
//	for (i = 1; i < suma; i++) {
//		factor *= factor;
//	}
//
//	int resultado = factor * determinante(submatriz, n);
//	return resultado;
//
//}
