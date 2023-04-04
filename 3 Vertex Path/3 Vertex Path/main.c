#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_adj;
    int* adj;
} vertex;

vertex* read_graph(int n) {
    vertex* E = malloc(n * sizeof(vertex));
    int n_adj;
    int c_vertex;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &n_adj);
        E[i].n_adj = n_adj;
        E[i].adj = malloc(n_adj * sizeof(vertex));
        
        for (int j = 0; j < n_adj; j++) {
            scanf("%d", &c_vertex);
            E[i].adj[j] = c_vertex;
        }
    }
    
    return E;
    
}

//depht first search
void dfs(vertex* E, int* colors, int from, int end) {
    colors[from] = 1; // Visito la sorgente colorandola di nero
    
    for (int i = 0; i < E[from].n_adj; i++) { // Visito in profondità ogni vertice adiacente
        int dest = E[from].adj[i]; // Ottengo la destinazione corrente
        
        if (colors[dest] == 0) { // Se il vertice è bianco, visitiamolo
            if (dest == end) { // Controllo che il vertice sia quello di destinazione desiderato
                colors[dest] = 1; // Se lo è, lo visitiamo e lo coloriamo di nero
                return;
            } else dfs(E, colors, dest, end); // Altrimenti continuiamo per profondità da quel vertice
        }
    }
}

int check_path(vertex* E, int n, int x, int y, int z) {
    int* colors = malloc(n * sizeof(int));
    
    // Inizializzo i colori
    for (int i = 0; i < n; i++) colors[i] = 0;
    
    // Provo a colorare se c'è
    dfs(E, colors, x, y);
    // Se y è bianco -> x e y non sono connessi tra di loro
    if (colors[y] == 0) return 0;
    
    // Reinizializzo i colori
    for (int i = 0; i < n; i++) colors[i] = 0;
    
    dfs(E, colors, y, z);
    // y e z sono connessi tra di loro?
    if (colors[z] == 0) return 0;
    
    return 1;
}

int main() {
    int n, x, y, z;
    vertex* graph = NULL;
    
    scanf("%d", &n);
    
    graph = read_graph(n);
    
    printf("WRITE X Y Z\n");
    scanf("%d %d %d", &x, &y, &z);
    
    if (check_path(graph, n, x, y, z) == 1) {
        printf("THERE IS A PATH THROUGH X -> Y -> Z\n");
    } else {
        printf("THERE ISN'T A PATH THROUGH X -> Y -> Z\n");
    }
    
    return 0;
}
