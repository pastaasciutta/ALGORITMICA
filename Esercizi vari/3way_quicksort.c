#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int three_way_partition(int a[], int sx, int px, int dx) {
	// Distinguo quelli < da quelli >=
	int tmp = a[px];
	a[px] = a[dx];
	a[dx] = tmp;
	 
	int x = a[dx];
	int i = sx - 1;
	for (int j = sx; j < dx; j++) {
		if (a[j] < x) {
			i = i + 1;
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}
	
	// Distinguo quelli > da quelli =
	// int t = i + 1;
	for (int j = i+1; j < dx;  j++) {
		if (a[j] == x) {
			i = i + 1;
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}
	
	tmp = a[i+1];
	a[i+1] = a[dx];
	a[dx] = tmp;
	
	return i+1;
}

void three_way_quicksort( int a[], int sx, int dx ) {
  
  int perno, pivot;
  if( sx < dx ) {
    pivot = (rand() % (dx - sx + 1)) + sx;

    perno = three_way_partition(a, sx, pivot, dx); /* separa gli elementi minori di a[pivot] 
					        da quelli maggiori o uguali */
    /* Ordina ricorsivamente le due metà */
    three_way_quicksort(a, sx, perno-1);
    three_way_quicksort(a, perno+1, dx);
    
  }

}

/* Lettura di un array di interi da input. 
Il primo elemento è la lunghezza dell'array */
int legge(int **a, int *len) {

  int i;
  scanf("%d", len);
  if(*len <= 0) return 1;

  *a = (int *) malloc(*len * sizeof(int));
  if(*a == NULL) return 1;

  for( i = 0; i < *len; i++ ) 
	  scanf("%d", (*a)+i);
  
  return 0;

}

int main() {
  
  int i, n, *A;

  if( legge(&A, &n)) return 1;

  srand(time(NULL));
  three_way_quicksort(A, 0, n-1);
  
  /* Stampa l'array ordinato */
  for( i = 0; i < n; i++ ) 
    printf("%d ", A[i]);
	
  return 0;
}

