// C program to demonstrate insert operation in binary search tree.
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// Creo la struttura per il grafo
typedef struct {
    int n_adj; // Rappresenta il numero di elementi nella lista di adiacenza (array)
    int* adj; // Array che rappresenta i vertici di adiacenza
    bool path; // cammino corrente
} vertex;


// Recursive DFS function
vertex* read_graph(int n);
void rec_dfs(vertex* graph, int* colors, int from,int n);
int is_graph_cycled(vertex* graph, int n, int from);

int main() {
    int n = 0, temp = 0;
    vertex* graph = NULL;

    scanf("%d", &n);

    graph = read_graph(n);

    // Creo l'array di colori
    int* colors = malloc(n * sizeof(int));

    // Inizializzo i colori in bianco (0)
    for (int i = 0; i < n; i++) colors[i] = 0;
    colors[0] = 1;

    rec_dfs(graph, colors, 0, n);

    return 0;
}

vertex* read_graph(int n) {

    vertex* E = malloc(n * sizeof(vertex));
    int arch_counter;
    int current_vertex;

    for (int i = 0; i < n; i++) {
        scanf("%d", &arch_counter);
        E[i].n_adj = arch_counter; // Imposto il numero di elementi nel vettore di adiacenza
        E[i].adj = malloc(arch_counter * sizeof(int)); // Alloco lo spazio per il vettore

        for (int j = 0; j < arch_counter; j++) {
            scanf("%d", &current_vertex);
            // Inserisco il vertice adiacente al vertice che sto valutando
            E[i].adj[j] = current_vertex;
        }
    }

    return E;
}


void rec_dfs(vertex* graph, int* colors, int from, int n) {
    int dest;
    // marco il cammino corrente
    graph[from].path = true;

    short i;
    for (i = 0; i < graph[from].n_adj; i++) {
        dest = graph[from].adj[i];
        if (colors[dest] == 0) {
            colors[dest] = 1;
            rec_dfs(graph, colors, dest, n);
        }
        else {
            if (!graph[dest].path) {
                puts("\n1");
                exit(0);
            }
        }
    }

    if (i == n - 1) puts("\n0");
    exit(0);

    graph[from].path = false;
}
