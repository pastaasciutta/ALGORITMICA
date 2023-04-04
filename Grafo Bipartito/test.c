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

int graph_color(vertex* E, int* colors, int from) {
    int dest;
    int result = 1;

    for (int i = 0; i < E[from].n_adj; i++) {
        dest = E[from].adj[i];
        if (colors[dest] == 0) {
            colors[dest] = -colors[from];

            // Se è tutto okay prosegui in profondità
            if (result != 0) {
                result = graph_color(E, colors, dest);
            } else {
                // Se dalla DFS ho ottenuto uno 0, vuol dire
            // che c'è stata qualche condizione tale per cui
            // il grafo non era bipartito
                break;
            }
            
        } else if (colors[dest] == colors[from]) {
            return 0; // Caso in cui i colori non sono alternati
        }
    }

    return result;

}

void is_bipartite(vertex* graph, int n) {
    int* colors = (int *) malloc(n * sizeof(int));
    int from = 0;

    // Inizializzo i colori
    for (int i = 0; i < n; i++) colors[i] = 0;
    colors[from] = -1;

    // Provo a colorare i risultati sperando di avere 
    // Una alternanza di colori
    int result = graph_color(graph, colors, from);

    printf("%d\n", result);
}

int main() {
    int n;
    vertex* graph = NULL;
    
    scanf("%d", &n);
    
    graph = read_graph(n);

    is_bipartite(graph, n);

    return 0;
}