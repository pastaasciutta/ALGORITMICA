#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struttura Nodo Albero
typedef struct _node {
    char key[101];
    struct _node* left;
    struct _node* right;
} node;

node* new_element(char* key) {
    node* new = malloc(sizeof(node));
    strcpy(new -> key, key);
    new -> left = NULL;
    new -> right = NULL;
    return new;
}

node* rec_insert(node* root, char* key) {
    if (root == NULL) {
        return new_element(key);
    }
    // key >= root -> key
    if (strcmp(key, root -> key) >= 0) {
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

//non è usata per un cazzo sta funzione
char* get_min_from(node* root) {
    // Caso in cui tento di fare il minimo, ma il nodo su cui vorrei farlo è nullo
    if (root == NULL) return NULL;
    
    node* cur = root;
    
    while (cur -> left != NULL) {
        cur = cur -> left;
    }
    
    return cur -> key;
}
//fine parte inutile 

char* prefix(node* root) {
    /* Se l'albero è vuoto non c'è un minimo. */
    if(root == NULL)
        return NULL;
    
    char* min;
    
    /* Il minimo del sottoalbero radicato in root
     * è il suo nodo più a sinistra.
     */
    min = prefix(root->left);
    
    if(min == NULL) {
        /* Se min è NULL vuol dire che siamo su una foglia.
         * In questo caso, secondo il testo dell'esercizio,
         * bisogna comunque stampare la chiave del nodo
         * (che è prefissa di se stessa)
         */
        printf(" %s\n", root->key);
    }
    else {
        /* Se invece non siamo su una foglia, verifichiamo
         * se il minimo è prefisso di questo nodo.
         */
        int len_min = strlen(min);
        int len_str = strlen(root->key);
        if(len_min <= len_str) { // Condizione (1)
            int i = 0;
            while(i < len_min) { // Condizione (2)
                if(min[i] != root->key[i])
                    break;
                i++;
            }
            /* Se con i abbiamo esaurito min, allora min è davvero prefisso. */
            if(i == len_min)
                printf("%s\n", root->key);
        }
    }
    
    /* Proseguiamo la visita nel sottoalbero destro */
    prefix(root->right);
    
    /* Se siamo arrivati su una foglia, root è il minimo di questo sottoalbero. */
    if(root->left == NULL)
        return root->key;
    
    /* Altrimenti restituiamo il minimo alle chiamate ricorsive. */
    return min;
}

int main() {
    int n;
    
    node* root = NULL;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        char* elem = (char *) malloc(101 * sizeof(char));
        scanf("%s", elem);
        root = rec_insert(root, elem);
    }
    
    prefix(root);
    
    deallocate(root);
}


