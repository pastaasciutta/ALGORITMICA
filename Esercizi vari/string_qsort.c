#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Scrivere un programma che utilizzi la funzione qsort per ordinare un array di stringhe. Le stringhe devono essere ordinate per lunghezza crescente. A parità di lunghezza, si utilizzi l’ordinamento lessicografico. Utilizzare una struct che memorizzi una stringa e la sua lunghezza per evitare di calcolare quest’ultima ad ogni confronto.
*/

struct string_info {
	char *str;
	int len;
};

typedef struct string_info STRING;

int compare(const void *a, const void *b) {
	// Elementi generico della lista di elementi composti (str, len).
	STRING **a1 = (STRING **) a;
	STRING **b1 = (STRING **) b;
	
	// Ottengo le lunghezze
	int len_a1 = (*a1) -> len;
	int len_b1 = (*b1) -> len;
	
	// Ottengo le loro stringhe
	char *str_a1 = (*a1) -> str;
	char *str_b1 = (*b1) -> str;
	
	// Se hanno la stessa lunghezza le comparo secondo l'ordinamento lessicografico
	if (len_a1 == len_b1) {
		return strcmp(str_a1, str_b1);
	}
	
	// Altrimenti le ordino in base alla loro lunghezza
	return (len_a1 - len_b1);
}

int main() {
	int i, N;
	scanf("%d", &N);
	
	// Alloco lo spazio di memoria per l'array di array di elementi strutturati
	STRING **a = malloc(N * sizeof(STRING *));
	
	// Inserisco stringhe ricavandone la loro lunghezza
	for (i = 0; i < N; i++) {
		// Alloco la memoria per l'array di string_info
		a[i] = (STRING *)malloc(101 * sizeof(STRING));
		// Alloco la memoria per l'array di char
		a[i] -> str = malloc(101 * sizeof(char));
		scanf("%s", (a[i] -> str));
		// Uso strlen per ottenere la lunghezza
		a[i] -> len = strlen(a[i] -> str);
	}
	
	// SORTING
	qsort(a, N, sizeof(char *), compare);
	
	for (i = 0; i < N; i++) {
		printf("%s -> %d\n", a[i] -> str, a[i] -> len);
		// Libero il garbage nell'array di stringhe e nell'array di string_info
		free(a[i] -> str);
		free(a[i]);
	}
	
	// Libero tutto
	free(a);
	
	return 0;
}
