/*
 ============================================================================
 Name        : Directiva-critical.c
 Author      : mirano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int f(int a) {
	return a;
}

int g(int b, int id) {
	int r = 0;
	for(int i =0; i<2;i++){
		r +=1;
		printf("---------%d %d\n", r, id);
	}
	return b;
}

int main(int argc, char *argv[]) {

	int max = 10;
	int x = 0;
	int res = 0;
	omp_set_num_threads(3);

	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		for (int i = 0; i < max; i++) {
			x = f(i);
			#pragma omp critical
			{
				res += g(x, id);
//				printf("%d %d %d\n", res, id, nt);
			}
		}

	}

	return 0;
}

