#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lunghezza massima dei nomi degli oggetti
#define MAXLEN 100

typedef struct item_ {
    char nome_oggetto[MAXLEN + 1];
    int valore_affettivo;
    struct item_ * next;
} item;

typedef struct table_ {
    item ** bins;
    int size;
} table;

// Funzione hash come descritta nel problema, 
// mod e' la dimensione della tabella
int hash(char * str, int mod) {
    unsigned int sum = 0;
    int i = 0;

    while(str[i] != '\0') {
        sum += (unsigned int)str[i];
        i++;
    }

    return sum % mod;
}

// Creazione di una nuova tabella hash
table * table_create(int size) {
    table * retVal = (table *)malloc(sizeof(table));
    retVal->size = size;
    retVal->bins = (item **)malloc(sizeof(item*)*size);

    int i; // Inizializzo le liste a NULL
    for (i = 0; i < size; i++) {
        retVal->bins[i] = NULL;
    }

    return retVal;
}

// Free della tabella
void table_destroy(table * t) {
    int i;
    item * cur, *prec;

    // Dealloco tutte le liste
    for (i = 0; i < t->size; i++) {
        cur = t->bins[i];
        while(cur) { // Scorro la lista corrente
            prec = cur;
            cur = cur->next;
            free(prec);
        }
    }

    // Libero l'array delle liste
    free(t->bins);
    free(t);
}

void table_insert(table* t, char* name, int aff) {
    int h = hash(name, t->size);

    item * cur = t->bins[h];
    // Ricerco il valore name nella tabella
    for(; cur != NULL; cur = cur->next) {
        if (strcmp(cur->nome_oggetto, name) == 0) { 
            // Ho trovato l'oggetto, sto inserendo un duplicato
            if(cur->valore_affettivo < aff) // Se necessario aggiorno il valore
                cur->valore_affettivo = aff;
            // Se l'oggetto era gia' presente ritorno senza inserire nulla
            return;
        }
    }
    
    // L'oggetto non e' un duplicato, lo aggiungo
    item* toInsert = (item*)malloc(sizeof(item));
    strcpy(toInsert->nome_oggetto, name);
    toInsert->valore_affettivo = aff;
    // Inserimento in testa
    toInsert->next = t->bins[h];
    t->bins[h] = toInsert;
}

// Ritorna un array contenente tutti gli oggetti della tabella
// Nella variabile count ritorna il numero di oggetti nell'array
item ** table_to_array(int * count, table * t) {
    // Ci sono al più' 30 oggetti (15 di Alice e 15 di Bob)
    item **retVal = (item**)malloc(sizeof(item*)* 30);

    int i, pos = 0;
    item *cur;
    // Percorro ogni lista
    for(i = 0; i < t->size; i++) {
        cur = t->bins[i];
        while (cur) { // Scorro la lista corrente e inserisco i nodi nell'array
            retVal[pos] = cur;
            cur = cur->next;
            pos++;
        }
    }

    // Assegno il contatore degli oggetti nell'array
    *count = pos;
    return retVal;
}

// Funzione per confontare due oggetti nell'array
int cmpfunc (const void * a, const void * b) {
    // Dereferenzio i due puntatori
    item * val_a = *(item**)a;
    item * val_b = *(item**)b;

    // Ordine decrescente in base al valore affattivo
    int ret = val_b->valore_affettivo - val_a->valore_affettivo;
    if (ret == 0) { // A parita' di valore affettivo, ordine lessicografico crescente
        return strcmp(val_a->nome_oggetto, val_b->nome_oggetto);
    }

    return ret;
}

int main() {
    int N, i, aff;
    char nome[MAXLEN + 1];

    // Leggo N
    scanf("%d", &N);

    // Istanzio una nuova tabella di dimensione 2N
    table* T = table_create(2 * N);

    for (i = 0; i < N; i++) { // Leggo gli oggetti in input
        scanf("%s", nome);
        scanf("%d", &aff);

        // Inserisco l'oggetti in tabella
        table_insert(T, nome, aff);
    }

    int count; // Ottengo gli oggetti nella tabella sotto forma di array
    item **oggetti = table_to_array(&count, T);
    
    // Ordino gli oggetti (nota: ogni oggetto dell'array e' un puntatore)
    qsort(oggetti, count, sizeof(item*), cmpfunc);

    // Stampo i primi 15 oggetti se ci sono almeno 15 oggetti, count altrimenti
    for(i = 0; i < 15 && i < count; i++) {
        printf("%s\n", oggetti[i]->nome_oggetto);
    }

    // Dealloco l'array usato per ordinare
    free(oggetti);
    // Dealloco la tabella
    table_destroy(T);

    return 0;
}