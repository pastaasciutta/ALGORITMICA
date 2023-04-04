#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_adj;
    int* adj;
} vertex;

vertex* read_graph(int n) {
    vertex* E = malloc(n * sizeof(vertex));
    
    // Inizializzo il grafo
    for (int i = 0; i < n; i++) {
        E[i].n_adj = 0;
    }
    
    int current_n_adj;
    int current_adj_vertex;
    
    for (int i =  0; i < n; i++) {
        
        scanf("%d", &current_n_adj);
        E[i].n_adj = current_n_adj;
        E[i].adj = malloc(current_n_adj * sizeof(int));
        
        for (int j = 0; j < current_n_adj; j++) {
            scanf("%d", &current_adj_vertex);
            E[i].adj[j] = current_adj_vertex;
        }
    }
    
    return E;
}

void graph_color(vertex* E, int* colors, int from) {
    int dest;

    for  (int i = 0; i < E[from].n_adj; i++) {
        dest = E[from].adj[i];
        if (colors[dest] == 0) {
            colors[dest] = 1;
            graph_color(E, colors, dest);
        }
    }
}

int is_connected(vertex* E, int n) {
    int colors[n];
    int from = 0;

    // Inizializzo i colori
    for (int i = 0; i < n; i++) {
        colors[i] = 0;
    }

    graph_color(E, colors, from);

    for (int i = 0; i < n; i++) {
        if (colors[i] == 0) {
            return 0;
        }
    }

    return 1;

}

int main() {
    int n;
    vertex* graph = NULL;
    
    scanf("%d", &n);
    
    graph = read_graph(n);

    printf("%d\n", is_connected(graph, n));

    return 0;
}