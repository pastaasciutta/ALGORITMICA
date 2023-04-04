#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void string_ins_sort(char **A, int len) {
	int i, j;
	char *key;
	
	for (i = 1; i < len; i++) {
		key = A[i];
		j = i - 1;
		while ((j >= 0) && (strcmp(A[j], key) > 0)) {
			A[j+1]=A[j]; // Scambio i puntatori
			j--;
		}
		A[j+1]=key;
	}
}

int main() {
	int i, N;
	
	scanf("%d", &N);
	
	char **a;
	a = (char **)malloc(N * sizeof(char *));
	
	for (i=0; i<N; i++) {
		a[i] = (char *)malloc(101 * sizeof(char));
		scanf("%s", a[i]);
	}
	
	string_ins_sort(a, N);
	
	// Print
	for (i=0; i<N; i++) {
		printf("MEMBER [%d]: %s\n",  i, a[i]);
	}
	
	// Terminazione
	for (i=0; i<N; i++) {
		free(a[i]);
	}
	
	free(a);
}
