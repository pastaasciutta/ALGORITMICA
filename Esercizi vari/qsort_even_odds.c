#include <stdio.h>
#include <stdlib.h>
#define N 6


/*
Scrivere un programma che utilizzi la funzione qsort e ordini un vettore di interi (in input), in modo da ottenere il seguente effetto. L’array ordinato deve contenere prima tutti i numeri pari e, a seguire, i numeri dispari. Si assuma che il numero 0 sia pari. I numeri pari devono essere ordinati in modo crescente fra di loro. I numeri dispari devono essere ordinati in modo decrescente fra di loro.
*/

int increasing_compare(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

int decreasing_compare(const void *a, const void *b) {
	return -(*(int*)a - *(int*)b);
}

int main() {
	int arr[N] = {11,12,3,6,-1,7};
	
	int i = -1;
	int tmp;
	for (int j = 0; j < N; j++) {
		if (arr[j] % 2 == 0) {
			i = i + 1;
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	
	int *px = &arr[i+1];
	
	qsort(arr, i+1, sizeof(int), increasing_compare);
	qsort(px, (N - (i+1)), sizeof(int), decreasing_compare);
	
	for (int i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	
	return 0;
}
