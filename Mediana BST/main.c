// qua non ho capito il senso della mediana 
#include <stdio.h>
#include <stdlib.h>

// Struttura Nodo Albero
typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;

node* new_element(int key) {
    node* new = malloc(sizeof(node));
    new -> key = key;
    new -> left = NULL;
    new -> right = NULL;
    return new;
}

node* rec_insert(node* root, int key) {
    if (root == NULL) {
        return new_element(key);
    }
    
    if (key >= root -> key) {
        root -> right = rec_insert(root -> right, key);
    } else {
        root -> left = rec_insert(root -> left, key);
    }
    
    return root;
}

// Libero la memoria
void deallocate(node* root) {
    if (root == NULL) return;
    
    deallocate(root -> left);
    deallocate(root -> right);
    
    free(root);
}

// Ottengo il numero di elementi di un albero data una radice
int count_nodes_at(node* from) {
    if (from == NULL) {
        return 0;
    }
    
    int count_left = count_nodes_at(from -> left); // Conto il numero degli elementi del sub sx
    int count_right = count_nodes_at(from -> right); // Conto il numero degli elementi del sub dx
    
    return count_left + count_right + 1; // Combino aggiungendo la radice
    
}

// Calcolo la mediana controllando che il numero degli elementi precedenti a root sia uguale a int(n/2)
void median(node* root, int target, int pre_counter) {
    
    // Caso base -> radice nulla
    if (root == NULL) {
        return;
    }
    
    // CASO 0
    // Caso base -> abbiamo trovato la mediana
    if (pre_counter == target) {
        printf("%d\n", root -> key);
        return;
    }
    
    // CASO 1
    // Se il pre_counter (Numero elementi che precedono root) è inferiore a int(n/2)
    // Allora dobbiamo andare a destra dell'albero, in modo che possiamo aumentare il precounter
    // Fino a farlo diventare uguale al target (int(n/2))
    if (pre_counter < target) {
        // Richiamo ricorsivamente la funzione sul nodo destro della radice, conservando il numero di elementi che precedevano
        // la radice + la radice stessa + il numero di elementi che la nuova radice (root -> right) ha nel suo sub sx
        // Questa operazione risulterà il pre_counter, quindi il numero di elementi che precedono la nuova radice (root -> right)
        median(root -> right, target, count_nodes_at(root -> right -> left) + pre_counter + 1);
    }
    
    // CASO 2
    // Nel caso in cui il numero di elementi che si trovano prima della radice siano superiori al target
    // Dobbiamo quindi passare a sinistra dell'albero, preimpostando il numero di elementi che ci sono nel sub sx di root -> left
    // Da qui ci possiamo ricondurre ai casi 0, 1, 2
    if (pre_counter > target) {
        median(root -> left, target, count_nodes_at(root -> left -> left));
    }
}

int main() {
    int n, elem;
    node* root = NULL;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        root = rec_insert(root, elem);
    }
    
    // Parto assegnando al pre counter il numero degli elementi che precedono la radice (sub sx)
    median(root, n/2, count_nodes_at(root -> left));
    
    deallocate(root);
}
