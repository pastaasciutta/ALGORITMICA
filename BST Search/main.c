#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* l;
    struct _node* r;
} node;

node* new_element(int key) {
    node* new = malloc(sizeof(node));
    new -> key = key;
    new -> l = NULL;
    new -> r = NULL;
    return new;
}

// Inserimento ricorsivo
node* rec_insert(node* root, int key) {
    // Caso base in cui il nodo radice del sotto albero che sto considerando è nulla
    if (root == NULL) {
        // In tal caso aggancio il nuovo nodo foglia creato dalla funzione new_element(int key)
        return new_element(key);
    }
    
    // Se la key è superiore della key del nodo radice, allora visita a dx, a sx altrimenti
    if (key > root -> key) {
        root -> r = rec_insert(root -> r, key);
    } else {
        root -> l = rec_insert(root -> l, key);
    }
    
    // Ritorno la radice principale aggiornata con il nuovo nodo foglia immesso
    return root;
}

// Ricerca ricorsiva
int rec_search(node* root, int key) {
    // Caso in cui la radice del sottoalbero che sto considerando è nulla
    // (elemento non trovato)
    if (root == NULL) {
        return -1;
    }
    // Caso in cui ho trovato l'elemento, segnalo cambiando found da -1 a 0
    if (root -> key == key) {
        return 0;
    }
    
    // Succede ogni volta che i due if precedenti non vengono verificati
    int found = -1;
    
    // Cerco a destra
    // Se ho trovato l'elemento found sarà 0, altrimenti continuerà ad essere -1
    // rec_search termina quando ho verificato un caso base
    // ovvero quando ho trovato un elemento oppure quando sono arrivato in fondo e l'elemento non c'è
    if (key > root -> key) {
        found = rec_search(root -> r, key);
    } else {
        found = rec_search(root -> l, key);
    }
    
    // Una volta che sono entrato in un caso base entri un una fase a cascata
    // Esempio. ho trovato il mio elemento alla profondità 2
    // L'ho trovato, found = 0, ma mi rimangono le due precedenti chiamate ricorsive da completare
    // Se found >= 0 allora le altre chiamate ricorsive le completo incrementando di 1
    // In tal caso ritorno quel valore che rappresenta la profondità
    // Altrimenti torna -1
    if (found >= 0) {
        return 1 + found;
    } else {
        return -1;
    }
    
}

// Libero la memoria
void deallocate(node* root) {
    if (root == NULL) {
        return;
    }
    
    // Vado a destra e a sinistra
    deallocate(root -> r);
    deallocate(root -> l);
    
    // Quando arrivo al caso base ovvero quando raggiungo la fine di un sottoalbero
    // Elimino ricorsivamente bottom-up
    free(root);
    
}

int main() {
    // Dimensione dell'albero
    int n = 0;
    // Intero di supporto per inserimento e ricerca
    int elem = 0;
    // Intero che memorizza la profondità dell'elemento che è stato trovato
    int depth = 0;
    // Creazione della radice
    node* root = NULL;
    
    // Chiediamo in input n
    scanf("%d", &n);
    
    // Chiediamo iterativamente l'input dei nodi dell'albero
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        // Ad ogni inserimento aggiorno l'albero di radice root
        root = rec_insert(root, elem);
    }
    
    // Entro in un ciclo infinito per chiedere gli input di ricerca
    while(1) {
        scanf("%d", &elem);
        // Se l'elemento è negativo allora esci
        if (elem < 0) {
            break;
        }
        
        // Effettuo la ricerca
        depth = rec_search(root, elem);
        
        // Se l'elemento non è stato trovato allora rec_search ritorna -1
        if (depth == -1) {
            printf("NO\n");
        } else {
            printf("%d\n", depth);
        }
        
    }
    
    // Freeing memory
    deallocate(root);
    
    
    return 0;
}

