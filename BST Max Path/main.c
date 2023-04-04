//Il programma deve stampare la chiave piu` piccola appartenente al cammino di somma massima.

#include <stdio.h>
#include <stdlib.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

// Struttura Nodo Albero
typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;

// Struttura che contiene la somma dei nodi che scorro e il minimo
// Mi servirà per adottare una soluzione ricorsiva dell'esercizio
typedef struct _info {
    int sum;
    int min;
} info;

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

info rec_heavier_path(node* root, int cur_min) {
    // Caso in cui la radice sia nulla
    // Caso base della ricorsione
    if (root == NULL) {
        info null_info;
        null_info.min = cur_min;
        null_info.sum = 0;
        
        return null_info;
    }
    
    // Variabili che contengono gli info del sotto albero di destra e di sinistra
    info info_left;
    info info_right;
    // Qualora il cammino max si trovasse a destra, il suo min sarebbe la radice
    // perchè si tratta di un BST
    
    // A sinistra quando faccio la chiamata ricorsiva tengo in memoria il nodo con chiave minima
    info_left = rec_heavier_path(root -> left, root -> key);
    // Mentre a destra non ho bisogno di memorizzarlo perchè il minimo sarà la chiave, quindi rimarrà sempre root -> key
    info_right = rec_heavier_path(root -> right, root -> key);
    
    // Caso in cui il cammino di somma massima si trova a sinistra
    // oppure sia a sinistra che a destra (prendo quello di sinistra perchè ha il minimo)
    if (info_left.sum >= info_right.sum) {
        info info_res;
        // Quando arrivo nella fase del ritorno a cascata della rircorsione
        // sommo nodo per nodo in modo da avere la somma del cammino alla fine
        info_res.sum = info_left.sum + root -> key;
        
        info_res.min = info_left.min;

        return info_res;
    } else {
        // Nel caso il cammino max si trovasse esclusivamente a destra => il minimo è la radice 
        info info_res;
        info_res.sum = info_right.sum + root -> key;
        info_res.min = root -> key; 
        
        return info_res;
    }
    
}

// Libero la memoria
void deallocate(node* root) {
    if (root == NULL) return;
    
    deallocate(root -> left);
    deallocate(root -> right);
    
    free(root);
}

int main() {
    int n, elem;
    node* root = NULL;
    
    scanf("%d", &n);
    
    // Risoluzione bruta del caso in cui n = 0
    // Inizialmente il crash era in questo caso, l'ho risolta banalmente così
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        root = rec_insert(root, elem);
    }
    
    info result;
    
    result = rec_heavier_path(root, root -> key);
    
    printf("%d\n", result.min);
    
    deallocate(root);
}

