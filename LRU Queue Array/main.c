#include <stdio.h>
#include <stdlib.h>

#define MIN(x,y) ((x) < (y)) ? (x) : (y)

typedef struct {
    int* values;
    int capacity;
    int element_counter;
} queue;

void queue_init(queue* q, int n) {
    q -> values = malloc(n * sizeof(int));
    q -> capacity = n;
    q -> element_counter = 0;
}

void deinit_queue(queue* q) {
    free(q -> values);
    q -> capacity = 0;
    q -> element_counter = 0;
}

/* Inserimento di un elemento in testa.
* Se l'elemento era già presente, la sua vecchia istanza viene cancellata
* spostando tutti gli elementi verso destra, sovrascrivendola.
* Tempo: O(n)
*/
void insert(queue* q, int element) {
    int temp;
    int previous = q -> values[0];
    int i;
    int is_found = 0;
    
    /* Se il primo elemento della coda è già quello che vogliamo inserire
    * possiamo terminare subito senza fare niente.
    */
    if(q->element_counter > 0 && q->values[0] == element) return;
    
    if (q -> element_counter == 1) {
        temp = q -> values[0];
        q -> values[0] = element;
        q -> values[1] = temp;
        q -> element_counter++;
        return;
    }
    
    /* E spostiamo verso destra tutti gli altri elementi.
    * In questo modo rimuoviamo automaticamente la coda.
    */
    for (i = 1; i < MIN(q -> element_counter + 1, q -> capacity); i++) {
        /* Tramite tmp1 e tmp2 effettuiamo degli scambi progressivi
        * fino alla fine della coda.
        */
        temp = q -> values[i];
        q -> values[i] = previous;
        
        if (temp == element) {
            /* Se abbiamo trovato k in coda vuol dire che gli elementi
            * successivi (cioè più vecchi) non devono essere espulsi
            * dal momento che stiamo solo "spostando" k in cima
            * e non inserendo un elemento nuovo. Quindi usciamo dal ciclo.
            */
            is_found = 1;
            break;
        }
        
        previous = temp;
    }
    
    /* Se abbiamo inserito un numero mai inserito finora
    * e se la coda non conteneva già il numero massimo di elementi,
    * aumentiamo il contatore del numero di elementi in coda.
    * (Si noti che questo contatore non diminuisce mai in questo esercizio).
    */
    if (is_found && q -> element_counter < q -> capacity) {
        q -> element_counter++;
    }
    
    /* Inseriamo k in testa (posizione 0) */
    q -> values[0] = element;
    
}

int main() {
    int n, element;
    int command;
    queue q;
    
    scanf("%d", &n);
    
    queue_init(&q, n);
    
    while (1) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &element);
                insert(&q, element);
                break;
            case 2:
                for (int i = 0; i < q.element_counter; i++) {
                    printf("%d ", q.values[i]);
                }
                printf("$\n");
            default:
                deinit_queue(&q);
                break;
        }
    }
    
    return 0;
}
