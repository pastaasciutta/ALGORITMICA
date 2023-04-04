//stampa ordinata dei nodi dell'albero
#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;

node* new_elem(int key) {
    node* new = malloc(sizeof(node));

    new -> key = key;
    new -> left = NULL;
    new -> right = NULL;
    
    return new;
}

node* rec_insert(node* root, int key) {
    // Quando si arriva a NULL, si alloca il nuovo nodo
    if (root == NULL) {
        return new_elem(key);
    }
    
    if (key > root -> key) {
        // Pensala così: l'elemento verrà inserito da qualche parte a destra della radice
        // una volta trovata la posizione e allocato il nuovo nodo, lo possiamo collegare con suo padre
        root -> right = rec_insert(root -> right, key);
    } else {
        root -> left = rec_insert(root -> left, key);
    }
    
    // Si ritorna la radice iniziale
    return root;
}

void deallocate(node* root) {
    if (root == NULL) {
        return;
    }
    
    deallocate(root -> left);
    deallocate(root -> right);
    
    free(root);
}

void inVisit(node* root) {
    if (root == NULL)
        return;
        
    inVisit(root -> left);
    printf("%d\n", root -> key);
    inVisit(root -> right);
}

int main() {
    int n;
    int elem;
    node* root = NULL;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        root = rec_insert(root, elem);
    }
    
    inVisit(root);
    
    deallocate(root);
    return 0;
}
