#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* next;
} node;

typedef struct {
    node* head;
    node* last;
} list;

// Inserisco in coda O(1)
node* insert(list* linked_list, int elem) {
    node* new = (node *) malloc(sizeof(node));
    new -> key = elem;
    new -> next = NULL;
    
    if (linked_list -> head == NULL) {
        linked_list -> head = new;
    } else {
        linked_list -> last -> next = new;
    }
    
    linked_list -> last = new;
    return linked_list -> head;
}

// Libero la memoria
void deallocate(node* head) {
    if (head == NULL) {
        return;
    }
    
    deallocate(head -> next);
    
    free(head);
}

// A partire da un nodo, sommo ricorsivamente andando verso destra
// accumulando il valore delle chiavi dei nodi che scorro
int rec_sum(node* from) {
    // Caso base ergo caso in cui ritorno a cascata
    if (from == NULL) {
        return 0;
    }
    // Variabile che accumula le somme ricorsive, durante la cascata ricorsiva
    int sum = rec_sum(from -> next);
    
    // Quando ho accumulato la somma, la aggiungo al valore della chiave corrente
    return sum + from -> key;
}

// Effettuo la somma ricorsivamente per ogni nodo della lista
void suffix_sums(node* head) {
    node* cur = head;
    
    while (cur != NULL) {
        cur -> key = rec_sum(cur -> next);
        cur = cur -> next;
    }
}

// Stampo la lista
void print_list(node* head) {
    node* cur = head;
    
    while (cur != NULL) {
        printf("%d ", cur -> key);
        cur = cur -> next;
    }
    
    printf("\n");
}

int main() {
    list linked_list;
    int n, elem;
    
    linked_list.head = NULL;
    linked_list.last = NULL;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        linked_list.head = insert(&linked_list, elem);
    }
    
    print_list(linked_list.head);
    
    suffix_sums(linked_list.head);
    
    print_list(linked_list.head);
    
    deallocate(linked_list.head);
    
    return 0;
}
