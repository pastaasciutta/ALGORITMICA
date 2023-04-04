#include <stdio.h>
#include <stdlib.h>
// Funzione che restituisce il max fra due numeri
#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
    int key;
    int occurrence;
} element;

// Singolo elemento della lista monodirezionale
typedef struct _node {
    element element;
    struct _node* next;
} node;

// Struttura di supporto con puntatori alla testa e alla coda
// della lista e dimensione della lista
typedef struct {
    node* head;
    node* last;
    size_t size;
} list;

// Struttura tabella hash contentente variabili di supporto che serviranno
//  per la soluzione di uno specifico esercizio
// In questo caso: la dimensione massima della lista piu grande e il numero di conflitti
typedef struct {
    size_t a, b, p;
    size_t size; // numero delle liste in tabella
    list* buckets; // puntatore alle liste
} hashtable;

// Funzione hash per una specifica tabella
size_t hash(const hashtable* table, int key) {
    return ((table -> a * key + table -> b) % table -> p) % table -> size;
}

// Inizializza una tabella di dimensione size e parametri a e b per la funzione
// di hashing
void hashtable_init(hashtable* table, size_t size, size_t a, size_t b) {
    table -> a = a;
    table -> b = b;
    table -> size = size;
    table -> p = 999149;
    // Alloco la memoria per contenere le chaining lists
    table -> buckets = malloc(size * sizeof(list));
    // Inizializzo la lista come vuota
    for (size_t i = 0; i < size; i++) {
        table -> buckets[i].head = NULL;
        table -> buckets[i].last = NULL;
        table -> buckets[i].size = 0;
    }
}

// Inserimento in coda lista monodirezionale
void list_append(list *l, int key) {
    node* new = malloc(sizeof(node));
    new -> element.key = key;
    new -> element.occurrence = 1;
    new -> next = NULL;
    
    // Caso lista vuota
    if (l -> size == 0) {
        l -> head = new;
    } else {
        l -> last -> next = new;
    }
    
    l -> last = new; // Memorizzo l'attuale ultimo elemento della lista
    l -> size++; // Incremento la grandezza della lista
}

// Inesrimento nella tabella hash
void hashtable_insert(hashtable* table, int key) {
    size_t h = hash(table, key);
    node* cur = table -> buckets[h].head;
    
    // Controllo se esiste l'elemento nella lista di trabocco
    while (cur != NULL) {
        if (cur -> element.key == key) {
            cur -> element.occurrence++; // Se esiste aumento il contatore delle occorrenze di quell'elemento
            return; // Ritorno
        }
        cur = cur -> next; // Avanzo cur
    }
    
    list_append(&table -> buckets[h], key); // Se l'elemento non è stato trovato -> lo aggiungo in coda
}

int main(int argc, char* argv[]) {
    size_t n;
    size_t occurrence_limit;
    int k;
    int* el_arr;
    int element_to_check;
    node* cur;
    node* tmp;
    hashtable table;
    
    scanf("%lu %lu", &n, &occurrence_limit);
    
    el_arr = (int *) malloc(n * sizeof(int));
    
    hashtable_init(&table, 2*n, 3, 7);
    
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &k);
        el_arr[i] = k;
        hashtable_insert(&table, k);
    }
    
    // Stampo solo gli elementi che hanno occorrenza almeno occurrence_limit
    for (size_t i = 0; i < n; i++) {
        element_to_check = el_arr[i];
        cur = table.buckets[hash(&table, element_to_check)].head;
        
        while (cur != NULL) {
            if (cur -> element.key == element_to_check) {
                if (cur -> element.occurrence >= occurrence_limit) {
                    printf("%d ", element_to_check);
                }
                break;
            }
            cur = cur -> next;
        }
        
    }
    
    printf("\n");
    
    for (int i = 0; i < 2*n; i++) {
        cur = table.buckets[i].head;
        
        while (cur != NULL) {
            tmp = cur;
            cur = cur -> next;
            free(tmp);
        }
    }
    
    return 0;
}
