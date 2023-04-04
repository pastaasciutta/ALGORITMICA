#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* next;
} node;

node* new_element(int key) {
    node* new = malloc(sizeof(node));
    new -> key = key;
    new -> next = NULL;
    return new;
}

node* rec_insert(node* head, int key) {
    if (head == NULL) {
        return new_element(key);
    }
    
    head -> next = rec_insert(head -> next, key);
    
    return head;
}

void delete_with_limit(node** head, int limit) {
    node* prec = *head;
    // Caso in cui l'elemento da eliminare è la testa
    while ((*head) -> key <= limit && *head != NULL) {
        *head = (*head) -> next;
        free(prec);
        prec = *head;
    }
    
    // Se la lista è diventata nulla topo le rimozioni in testa, allora ritorna
    // Se la lista è composta di un solo elemento dopo le rimozioni in testa, allora ritorna
    if (*head == NULL || (*head) -> next == NULL) return;
    
    // Caso in cui la lista c'è ed è composta da più di un elemento
    node* current = (*head) -> next;
    
    while (current != NULL) {
        // Caso in cui dobbiamo eliminare l'elemento corrente
        if (current -> key <= limit) {
            prec -> next = current -> next;
            free(current);
            current = prec -> next;
        } else { // Caso in cui non dobbiamo eliminare l'elemento (sposto solo i puntatori in avanti)
            prec = current;
            current = current -> next;
        }
    }
    
}

void print_list(node* head) {
    node* cur = head;
    
    while (cur != NULL) {
        printf("%d ", cur -> key);
        cur = cur -> next;
    }
    
    printf("\n");
}

void deallocate(node* head) {
    if (head == NULL) return;
    
    deallocate(head -> next);
    
    free(head);
}

int main() {
    int n, elem;
    int sum = 0;
    int avg = 0;
    node* head = NULL;
    
    scanf("%d", &n);
    
    if (n == 0) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        head = rec_insert(head, elem);
        sum += elem;
    }
    
    avg = sum/n;
    
    printf("%d\n", avg);
    
    print_list(head);
    
    // Elimina tutti gli elementi della lista al di sotto di quel valore
    delete_with_limit(&head, avg);
    
    print_list(head);
    
    deallocate(head);
    
    return 0;
}
