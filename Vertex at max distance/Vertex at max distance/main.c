/*Sia G = (V, E) un grafo connesso e non orientato. Progettare un  algortimo  che  ricevuto  in  ingresso  G  e  un  suo  vertice  r, restituisca  il  numero  di  vertici  che  si  trovano  a  distanza massima da r. */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_adj;
    int* adj;
} vertex;

typedef struct {
    int* values;
    int capacity;
    int back_index;
    int front_index;
} queue;

void queue_init(queue* q, int n) {
    q -> values = malloc(n * sizeof(int));
    q -> capacity = n;
    q -> back_index = 0;
    q -> front_index = 0;
}

void queue_pushBack(queue* q, int value) {
    q -> values[q -> back_index] = value;
    
    q -> back_index++;
    
    if (q -> back_index > q -> capacity) {
        q -> back_index = 0;
    }
}

int queue_popFront(queue* q) {
    int value = q -> values[q -> front_index];
    
    q -> front_index++;
    
    if (q -> front_index > q -> capacity) {
        q -> front_index = 0;
    }
    
    return value;
}

int is_queue_empty(queue* q) {
    if (q -> back_index == q -> front_index) {
        return 1;
    }
    
    return 0;
}

vertex* read_graph(int n) {
    vertex* E = malloc(n * sizeof(vertex));
    int c_n_adj;
    int c_adj;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &c_n_adj);
        E[i].n_adj = c_n_adj;
        E[i].adj = malloc(c_n_adj * sizeof(int));
        
        for (int j = 0; j < c_n_adj; j++) {
            scanf("%d", &c_adj);
            E[i].adj[j] = c_adj;
        }
    }
    
    return E;
}

// Uso la BFS
int count_vertex_at_max_distance(vertex* E, int n, int from) {
    int* distances = (int *) malloc(n * sizeof(int));
    int dest;
    int src;
    int max = -1;
    int counter = 0;
    int cur_max_dist = 0;
    
    queue q;
    
    // Inizializzo le distanze
    for (int i = 0; i < n; i++) distances[i] = -1;
    distances[from] = 0;
    
    // Inizializzo la coda
    queue_init(&q, n);
    queue_pushBack(&q, from);
    
    while (!is_queue_empty(&q)) {
        src = queue_popFront(&q);
        
        for (int i = 0; i < E[src].n_adj; i++) {
            dest = E[src].adj[i];
            
            if (distances[dest] == -1) {
                distances[dest] = distances[src] + 1;
                
                queue_pushBack(&q, dest);

                if (distances[src] > cur_max_dist) {
                    cur_max_dist = distances[src];
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (distances[i] == max) {
            counter++;
        }
    }
    
    return counter;
}

int main() {
    int n;
    vertex* graph = NULL;
    
    scanf("%d", &n);
    
    graph = read_graph(n);
    
    printf("%d\n", count_vertex_at_max_distance(graph, n, 0));
    
    return 0;
}
