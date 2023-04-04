//trova la stringa di valore massimo appartenente a un certo sottoalbero (sub root)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} node_element;

//bin tree
typedef struct _node {
    node_element element;
    struct _node* l;
    struct _node* r;
} node;

//alloco nuovo nodo del BT
node* new_element(char* key, int value) {
    node* new = malloc(sizeof(node));
    //alloco spazio per stringa key
    new -> element.key = (char *) malloc(101 * sizeof(char));
    strcpy(new -> element.key, key);
    new -> element.value = value;
    new -> l = NULL;
    new -> r = NULL;
    return new;
}

// Inserimento ricorsivo del nodo
node* rec_insert(node* root, char* key, int value) {
    // Caso base in cui il nodo radice del sotto albero che sto considerando è nulla
    if (root == NULL) {
        // In tal caso aggancio il nuovo nodo foglia creato dalla funzione new_element(int key)
        return new_element(key, value);
    }
    
    // Se la key è superiore della key del nodo radice, allora visita a dx, a sx altrimenti
    if (strcmp(key, root -> element.key) >= 0) {
        root -> r = rec_insert(root -> r, key, value);
    } else {
        root -> l = rec_insert(root -> l, key, value);
    }
    
    // Ritorno la radice principale aggiornata con il nuovo nodo foglia immesso
    return root;
}



// delete BT
void deallocate(node* root) {
    if (root == NULL) {
        return;
    }
    
    // Vado a destra e a sinistra
    deallocate(root -> r);
    deallocate(root -> l);
    
    // Quando arrivo al caso base ovvero quando raggiungo la fine di un sottoalbero
    // Elimino ricorsivamente bottom-up
    free(root -> element.key);
    free(root);
    
}

// Effettuo la ricerca per stringhe
node* rec_search(node* root, char* key) {
    if (root == NULL) return NULL;

    if (strcmp(key, root -> element.key) > 0) {
        return rec_search(root -> r, key);
    } else if (strcmp(key, root -> element.key) < 0) {
        return rec_search(root -> l, key);
    }

    return root;
}

//NB non è molto efficiente basterebbe anadare a destra nel sottoalbero
int max_value_in_subtree(node* sub_root) {
    if (sub_root == NULL) return 0;

    // Calcola il max a sinistra e a destra
    int left_max = max_value_in_subtree(sub_root -> l);
    int right_max = max_value_in_subtree(sub_root -> r);

    // Ritorno il max tra il sub albero di sx, quello di dx e la radice
    if (left_max >= right_max) {
        if (left_max > sub_root -> element.value) {
            return left_max;
        } else {
            return sub_root -> element.value;
        }
    } else {
        if (right_max > sub_root -> element.value) {
            return right_max;
        } else {
            return sub_root -> element.value;
        }
    }
}

int main() {
    // Dimensione dell'albero
    int n = 0;
    // Intero di supporto per inserimento e ricerca
    char* elem = (char *) malloc(101 * sizeof(char));
    int elem_val;
    // Creazione della radice
    node* root = NULL;
    
    // Chiediamo in input n
    scanf("%d", &n);
    
    // Chiediamo iterativamente l'input dei nodi dell'albero
    for (int i = 0; i < n; i++) {
        scanf("%s", elem);
        scanf("%d", &elem_val);
        // Ad ogni inserimento aggiorno l'albero di radice root
        root = rec_insert(root, elem, elem_val);
    }
    
    scanf("%s", elem);

    node* sub_root = rec_search(root, elem);

    printf("%d\n", max_value_in_subtree(sub_root));
    
    // Freeing memory
    deallocate(root);
    
    return 0;
}

