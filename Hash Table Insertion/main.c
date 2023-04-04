#include <stdio.h>
#include <stdlib.h>

// Singolo elemento della lista monodirezionale
typedef struct _node {
     int key;
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
     size_t max_bucket_size;
     size_t num_conflicts;
} hashtable;

// Inserimento in coda lista monodirezionale
void list_append(list *l, int key) {
     node* new = malloc(sizeof(node));
     new -> key = key;
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
     table -> max_bucket_size = 0;
     table -> num_conflicts = 0;
     // Alloco la memoria per contenere le chaining lists
     table -> buckets = malloc(size * sizeof(list));
     // Inizializzo la lista come vuota
     for (size_t i = 0; i < size; i++) {
          table -> buckets[i].head = NULL;
          table -> buckets[i].last = NULL;
          table -> buckets[i].size = 0;
     }
}

// Funzione che restituisce il max fra due numeri
#define max(x, y) ((x) > (y) ? (x) : (y))

// Inesrimento nella tabella hash
void hashtable_insert(hashtable* table, int key) {
     size_t h = hash(table, key);

     list_append(&table -> buckets[h], key);
     table -> max_bucket_size = max(table -> max_bucket_size, table -> buckets[h].size);

     // Se abbiamo inserito in una lista non vuota, dobbiamo incrementare
     // il contatore delle collisioni
     // Quindi se dopo che abbiamo inserito, la dimensione della lista != 1
     // Vuol dire che c'e' stato una collisione
     if (table -> buckets[h].size != 1) {
          table -> num_conflicts++;
     }
}

int main(int argc, char* argv[]) {
     size_t n, a, b;
     int k;

     scanf("%lu %lu %lu", &n, &a, &b);

     hashtable table;

     hashtable_init(&table, 2*n, a, b);

     for (size_t i = 0; i < n; i++) {
          scanf("%d", &k);
          hashtable_insert(&table, k);
     }

     printf("%lu\n", table.max_bucket_size);
     printf("%lu\n", table.num_conflicts);

     return 0;
}
