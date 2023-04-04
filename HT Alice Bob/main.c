#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x, y) ((x) < (y) ? (x) : (y))

typedef struct _node {
    char name[101]; // 100 character string
    int value;
    struct _node* next;
} node;

typedef struct {
    node* head;
    size_t size;
} list;

typedef struct {
    size_t size;
    list* buckets;
} HT;

void hashtable_init(HT* table, size_t size) {
    // Hashtable properties
    table -> size = size;
    table -> buckets = malloc(size * sizeof(list));

    // Linked Lists properties initialized
    for (int i = 0; i < size; i++) {
        table -> buckets[i].head = NULL;
        table -> buckets[i].size = 0;
    }
}

//funzione di hashing
size_t hash(HT* table, char name[]) {
    int i = 0;
    char current_char = name[0];
    int sum = 0;

    // Sommo il codice decimale ASCII per ogni carattere della stringa
    while (current_char != '\0') {
        current_char = name[i];
        sum += current_char;
        i++;
    }

    // Ritorno la somma modulo dimensione della tabella
    return sum % table -> size;
} 

// Head insertion
void list_append(list* l, char name[], int val) {
    node* new = malloc(sizeof(node));
    // Ricorda di usare STRCPY e STRCMP
    strcpy(new -> name, name);
    new -> value = val;

    if (l -> head == NULL) {
        new -> next = NULL;
    } else {
        new -> next = l -> head;
    }

    l -> head = new;
    l -> size++;
}

void hashtable_insert(HT* table, char name[], int val) {
    size_t h = hash(table, name);
    node* current = table -> buckets[h].head;

    // Controllo che ci sia o meno l'elemento da inserire
    // Se l'elemento non c'è, lo inserisco in testa con list_append
    while (current != NULL)
    {
        // Caso in cui l'elemento è un doppione allora prendiamo il più grande per valore affettivo
        if (strcmp(current -> name, name) == 0) {
            if (current -> value < val) {
                current -> value = val;
            }
            return;
        }
        // Se non ho trovato l'elemento, avanzo con il puntatore lungo la lista
        current = current -> next;
    }
    
    // Caso in cui l'elemento non c'è
    // Inserimento Costante
    list_append(&table -> buckets[h], name, val);
}

// Funzione di comparazione per QSORT
int cmpfunc (const void *a, const void *b) {
    // Faccio il type casting da const void al tipo di dato che mi interessa
    node* vA = ((node *)a);
    node* vB = (node *)b;

    // Caso in cui A e B sono diversi, metto prima quello con valore più grande
    if (vA -> value != vB -> value) {
        return -(vA -> value - vB -> value);
    }
    
    // Caso in cui valA e valB sono uguali, allora metto prima quello con stringa crescente
    return (strcmp(vA -> name, vB -> name));
}

//  Funzione che stampa i primi 15
void get_objects(HT ht) {
    node arr[30]; // Array di appoggio che mi serve per ordinare
    node* cur = NULL; // Puntatore che scorre la lista di trabocco
    int last_index = 0; // Variabile che si segna l'ultimo indice dell'array di ordinamento

    for (int i = 0; i < ht.size; i++) {
        // Ad ogni ciclo, quando finisco di esaminare la lista, imposto il puntatore ad un'altra cella
        cur = ht.buckets[i].head;
        while (cur != NULL) {
            strcpy(arr[last_index].name, cur -> name); // Copiamo ogni elemento della tabella (ogni lista) nell'array arr
            arr[last_index].value = cur -> value;
            arr[last_index].next = NULL;
            last_index++; // Man mano che inseriamo ci teniamo salvato l'indice dell'ultimo elemento dell'array
            cur = cur -> next; // Avanziamo con il puntatore nella lista di trabocco
        }
    }

    // Ordino l'array secondo le regole dell'esercizio
    qsort(arr, last_index, sizeof(node), cmpfunc);

    // Se gli elementi dell'array sono più di 15 allora prendiamo i primi 15, altrimenti prendiamo quelli che stanno
    if (last_index > 15) {
        for (int i = 0; i < 15; i++) {
            printf("%s\n", arr[i].name);
        }
    } else {
        for (int i = 0; i < last_index; i++) {
            printf("%s\n", arr[i].name);
        }
    }

}

int main() {
    size_t n;
    char name[101];
    int value = 0;
    HT ht;

    scanf("%lu", &n);

    // Inizializzo la tabella
    hashtable_init(&ht, 2*n);

    // Inserisco elementi in tabella
    for (int i = 0; i < n; i++) {
        scanf("%s", name);
        scanf("%d", &value);
        hashtable_insert(&ht, name, value);
    }

    // Ottengo i primi 15 alpiù
    get_objects(ht);

    return 0;
}