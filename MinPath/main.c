#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_adj;
    int* adj;
} vertex;

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

vertex* read_graph(int n) {
    vertex* E = malloc(n * sizeof(vertex));
    int current_n_adj;
    int current_vertex;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &current_n_adj);
        E[i].n_adj = current_n_adj;
        E[i].adj = malloc(current_n_adj * sizeof(int));

        for (int j = 0; j < current_n_adj; j++) {
            scanf("%d", &current_vertex);
            E[i].adj[j] = current_vertex;
        }
    }

    return E;
}

int single_bfs(vertex* E, int n, int from, int end) {

    // Se from = end -> Stiamo calcolando la distanza da un nodo a se stesso
    if (from == end) return 0;

    int* distances = (int *) malloc(n * sizeof(int));
    int dest, src;
    queue q;
    int i;

    // Inizializzo l'array di distanze
    for (int i = 0; i < n; i++) distances[i] = -1;
    distances[from] = 0; // Il nodo di partenza ha distanza 0 da se stesso

    // Inizializzo la coda
    queue_init(&q, n);
    // Inserisco il vertice from nella coda 
    queue_pushBack(&q, from);

    while(!is_queue_empty(&q)) {
        src = queue_popFront(&q);
        
        for(i = 0; i < E[src].n_adj; i++) {
            dest = E[src].adj[i];
            
            // Caso in cui l'elemento non è stato ancora visitato
            if (distances[dest] == -1) {
                distances[dest] = distances[src] + 1;

                if (dest == end) {
                    int result = distances[dest];

                    deinit_queue(&q);
                    free(dest);
                    return result;
                }

                queue_pushBack(&q, dest);
            }
        }
    }

    deinit_queue(&q);
    free(distances);
    return -1;
}



int main() {
    int n;
    int n_query;
    int query_from;
    int query_to;
    vertex* graph = NULL;

    scanf("%d", &n);

    graph = read_graph(n);

    scanf("%d", &n_query);
    
    for (int i = 0; i < n_query; i++) {
        scanf("%d %d", &query_from, &query_to);
        printf("%d\n", single_bfs(graph, n, query_from, query_to));
    }

    return EXIT_SUCCESS;
}