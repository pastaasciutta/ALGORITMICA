#include <stdio.h>
#include <stdlib.h>

typedef struct _nodo {
    int info;
    int print; // valore che memorizza se un nodo deve essere stampato o meno
    struct _nodo* left;
    struct _nodo* right;
} nodo;

// visita ricorsiva post-order per il calcolo di L e R per ciascun nodo
void lrvisit(nodo* u, int* L, int* R) {
    if(u == NULL) return;

    int curent_max =0;
    int max =0;
    int leftL = -1, rightR = -1; // variabili da passare ai figli, inizializzate a -1
    // in modo che se un nodo non ha un figlio sinistro (destro) il suo valore di L (R) valga 0
    int t = -1; // dato che solo L del figlio sinistro e R del figlio destro servono ad u per calcolare
    // i propri valori di L e R passiamo t ai figli per gli altri due casi che non ci interessano
    lrvisit(u->left, &leftL, &t);
    lrvisit(u->right, &t, &rightR);

    // u calcola L e R a partire dai valori ottenuti dai figli
    *L = leftL + 1;
    *R = rightR + 1;
    current_max = abs(*L - *R);
    if(current_max > max){
      max = current_max;
    }

}

// visita ricorsiva in-order per stampare i nodi per cui L > U
void lrprint(nodo* u) {
    if(u == NULL) return;

    lrprint(u->left);
    if(u->print == 1) printf("%d\n", u->info); // stampiamo u solo se L > R
    lrprint(u->right);
}

// allocazione e inizializzazione di un nodo
nodo* crea_nodo(int v) {
    nodo* res = (nodo*)malloc(sizeof(nodo));
    res->info = v;
    res->print = 0; // print è inizializzato a 0 in modo che di base nessun nodo venga stampato
    res->left = NULL;
    res->right = NULL;

    return res;
}

// inserimento ricorsivo di un nodo
nodo* inserisci(nodo* root, int v) {
    if(root == NULL) return crea_nodo(v);

    if(v <= root->info) {
        root->left = inserisci(root->left, v);
    } else {
        root->right = inserisci(root->right, v);
    }

    return root;
}

// liberazione della memoria occupata dall'albero in modo ricorsivo
void free_albero(nodo* root) {
    if(root == NULL) return;

    free_albero(root->left);
    free_albero(root->right);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);

    nodo *root = NULL;
    for(int i = 0; i<n; ++i) {
        int v;
        scanf("%d", &v);
        root = inserisci(root, v);
    }

    int L, R;
    lrvisit(root, &L, &R); // visita per il calcolo di L e R per ciascun nodo
    lrprint(root); // stampa dei nodi per cui L > R

    free_albero(root);

    return 0;
}
