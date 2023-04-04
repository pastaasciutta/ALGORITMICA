#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_edges;
    int* edges;
} edge;

// Ho bisogno di usare la Queue per usare la BFS
typedef struct {
    int* values; // Valori attuali della coda
    int capacity; // Capacità della coda
    int back_index; // Inserisco da qui
    int front_index; // Prendo da qui
} queue;

// Inizializzo la coda
void queue_init(queue* q, int n) {
    q -> capacity = n; // La capacità è tanto quanto il numero dei vertici nel grafo
    q -> values = malloc(n * sizeof(int)); // Alloco la memoria per i valori interi
    q -> back_index = 0; 
    q -> front_index = 0;
}

// inserimento nell array 
void queue_pushBack(queue* q, int value) {
    q -> values[q -> back_index] = value; // Inserisco in back_index

    q -> back_index++; // Mando avanti il back_index

    // Se è arrivato oltre la capacità massima -> ritorna a 0
    if (q -> back_index > q -> capacity) {
        q -> back_index = 0;
    }

}

int queue_popFront(queue* q) {
    // Ottengo da front_index
    int value_taken = q -> values[q -> front_index];

    // Mando avanti il front_index
    q -> front_index++;

    // Se è arrivato oltre la capacità massima -> ritorna a 0
    if (q -> front_index > q -> capacity) {
        q -> front_index = 0;
    }

    // Ritorna il valor ottenuto
    return value_taken;
}

int is_queue_empty(queue* q) {
    if (q -> back_index == q -> front_index) {
        return 1; // empty
    }

    return 0; // not empty
}

void deinit_queue(queue* q) {
    free(q -> values);
    q -> capacity = 0;
    q -> front_index = q -> back_index = 0;
}

edge* read_graph(int n) {
    edge* E = malloc(n * sizeof(edge));
    int num;
    int curr_edges;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        E[i].n_edges = num;
        E[i].edges = malloc(num * sizeof(int));

        for (int j = 0; j < num; j++) {
            scanf("%d", &curr_edges);
            E[i].edges[j] = curr_edges;
        }
    }

    return E;
}

int single_bfs(edge* E, int n, int from) {
    // Ho bisogno di un array che mi tenga le distanze
    int* distances = (int *) malloc(n * sizeof(int));
    // Ho bisogno di immagazzinare una variabile che tenga conto
    // ogni volta del nodo di destinazione
    // Ho bisogno di una variabile che tenga conto della radice da
    // cui stiamo partendo per calcolare la distanza (src,dest)
    int dest, src;
    // Ho bisogno di una coda che mi ricordi degli elementi adiacenti che devo ancora analizzare
    queue q;
    // Indice per scorrere gli elementi adiacenti
    int i;
    // Variabile che contiene il più lungo cammino minimo dal vertice from agli altri vertici
    int max = 0;

    // Inizializzo l'array di distanze
    for (int i = 0; i < n; i++) distances[i] = -1;
    distances[from] = 0; // Il nodo di partenza ha distanza 0 da se stesso

    // Inizializzo la coda
    queue_init(&q, n);
    // Inserisco il vertice from nella coda 
    queue_pushBack(&q, from);

    while(!is_queue_empty(&q)) {
        src = queue_popFront(&q);
        
        for(i = 0; i < E[src].n_edges; i++) {
            dest = E[src].edges[i];
            
            // Caso in cui l'elemento non è stato ancora visitato
            if (distances[dest] == -1) {
                distances[dest] = distances[src] + 1;
                max = distances[dest];
                queue_pushBack(&q, dest);
            }
        }
    }

    // Controllo che il grafo sia connesso (lo faccio solo perchè me lo chiede l'esercizio)
    for (int i = 0; i < n; i++) {
        if (distances[i] == -1) {
            return -1;
        }
    }

    deinit_queue(&q);
    free(distances);
    return max;
}

int max_shortest_path(edge *E, int n) {
    // Variabile che mi contiene il più lungo cammino minimo
    int max_shortest_path = 0;
    // Indice per i vertici del grafo
    int i;

    // Faccio la bfs a partire da ogni nodo del grafo
    for (i = 0; i < n; i++) {
        int possible_max = single_bfs(E, n, i); // Mi calcolo il più lungo cammino minimo a partire dal vertice i-esimo
        
        // Se il grafo non è connesso ritorno -1
        if (possible_max == -1) {
            return -1;
        }

        if (possible_max > max_shortest_path) { // Confronto con il max di tutti fino a questo momento
            max_shortest_path = possible_max;
        }
    }

    return max_shortest_path;
}

int main() {
    int n;
    edge* graph = NULL;

    scanf("%d", &n);

    graph = read_graph(n);
    
    printf("%d\n", max_shortest_path(graph, n));

    return 0;
}