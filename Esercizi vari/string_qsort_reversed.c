#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Scrivere un programma che legga in input un array A di stringhe e che utilizzi la funzione qsort per ordinare in ordine alfabetico decrescente le stringhe in input. Assumere che la lunghezza massima di una stringa sia 100 caratteri.
*/
int decreasing_compare(const void *a, const void *b) {
	char **a1 = (char **) a;
	char **b1 = (char **) b;
	
	return -(strcmp(*a1, *b1));
}

int main() {
	int i, N;
	scanf("%d", &N);
	
	char **arr;
	arr = (char **)malloc(N * sizeof(char *));
	
	for (i = 0; i < N; i ++) {
		arr[i] = (char *)malloc(101 * sizeof(char));
		scanf("%s", arr[i]);
	}
	
	qsort(arr, N, sizeof(char *), decreasing_compare); 
	
	for (i = 0; i < N; i++) {
		printf("- %s;\n", arr[i]);
		free(arr[i]);
	}
	
	free(arr);
	
	return 0;
}
