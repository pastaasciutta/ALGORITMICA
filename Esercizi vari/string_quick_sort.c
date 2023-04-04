#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int partition(char **a, int sx, int px, int dx) {
	char *tmp = a[px];
	a[px] = a[dx];
	a[dx] = tmp;
	 
	char *x = a[dx];
	int i = sx - 1;
	for (int j = sx; j < dx; j++) {
		if (strcmp(a[j], x) <= 0) {
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

void quicksort(char **a, int sx, int dx ) {
  
  int perno, pivot;
  if( sx < dx ) {
    pivot = (rand() % (dx - sx + 1)) + sx;

    perno = partition(a, sx, pivot, dx); /* separa gli elementi minori di a[pivot] 
					        da quelli maggiori o uguali */
    /* Ordina ricorsivamente le due metà */
    quicksort(a, sx, perno-1);
    quicksort(a, perno+1, dx);
    
  }

}

int main() {
  
  int i, n;
  scanf("%d", &n); 
  
  char **a;
  a = (char **)malloc(n * sizeof(char *));
  
  // Read strings
  for (i = 0; i < n; i++) {
  	a[i] = (char *)malloc(101 * sizeof(char));
  	scanf("%s",  a[i]);
  }
  
  srand(time(NULL));
  quicksort(a, 0, n-1);
	
	// Print strings
	for (i = 0; i < n; i++) {
		printf("ELEMENT {%d}: %s\n", i, a[i]);
	}
	
	// Free memory
	for (i = 0; i < n; i++) {
		free(a[i]);
	}
	free(a);
	
  return 0;
}
