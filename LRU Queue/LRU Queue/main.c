#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int value;
    struct _node* next;
    struct _node* prev;
} node;

typedef struct {
    node* head;
    int size;
} queue;

// Inizializzo la coda
queue init_queue() {
    queue q;
    
    q.head = NULL;
    q.size = 0;
    
    return q;
}

// Funzione per la ricerca che restituisce il puntatore dell'elemento cercato
// Se l'elemento non esiste -> ritorna NULL
node* search_element_in_queue(queue q, int key) {
    node* pointer_to_key = q.head;
    
    while (pointer_to_key != NULL) {
        if (pointer_to_key -> value == key) {
            return pointer_to_key;
        }
        pointer_to_key = pointer_to_key -> next;
    }
    
    return pointer_to_key;
}

// Inserisco in testa
void head_insertion(queue* q, int n, int key) {
    node* new = (node *) malloc(sizeof(node));
    
    new -> next = q -> head;
    new -> value = key;
    new -> prev = NULL;
    
    if (q -> head != NULL) {
        q -> head -> prev = new;
    }
    
    q -> head = new;
    q -> size++;
    
    if (q -> size > n) {
        // Elimina l'elemento in coda
        node* last = q -> head;
        
        while (last -> next != NULL) {
            last = last -> next;
        }
        
        last -> prev -> next = NULL;
        free(last);
        q -> size--;
    }
}

// MARK: - Occhio ai puntatori e ai vari casi!!!
void replace(queue* q, node* key_node) {
    
    if (q -> head -> value == key_node -> value) {
        return;
    }
    
    key_node -> prev -> next = key_node -> next;
    
    if (key_node -> prev -> prev == NULL) {
        key_node -> prev -> prev = key_node;
    }
    
    if (key_node -> next != NULL) {
        key_node -> next -> prev = key_node -> prev;
    }
    
    key_node -> next = q -> head;
    q -> head -> prev = key_node;
    key_node -> prev = NULL;
    
    q -> head = key_node;
    
}

void print_queue(queue q) {
    node* current = q.head;
    
    while (current != NULL) {
        printf("%d ", current -> value);
        current = current -> next;
    }
    
    printf("$\n");
}

void print_reverse(queue q) {
    node* current = q.head;
    
    while (current != NULL) {
        
        if (current -> prev == NULL) {
            printf("\n----PREV OF {%d} IS NULL ", current -> value);
        } else {
            printf("\n----PREV OF {%d} IS %d", current -> value, current -> prev -> value);
        }
        
        if (current -> next == NULL) {
            printf("\n----NEXT OF {%d} IS NULL ", current -> value);
        } else {
            printf("\n----NEXT OF {%d} IS %d", current -> value, current -> next -> value);
        }
        
        current = current -> next;
    }
    
    printf("$\n");
}

int main() {
    int n;
    int command;
    int elem_to_insert;
    queue q;
    
    scanf("%d", &n);
    
    // Inizializzo la coda
    q = init_queue();
    
    while (1) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &elem_to_insert);
                node* to_elem = search_element_in_queue(q, elem_to_insert);
                if (to_elem == NULL) {
                    head_insertion(&q, n, elem_to_insert);
                } else {
                    replace(&q, to_elem);
                }
                break;
            case 2:
                print_queue(q);
                break;
            default:
                return 0;
                break;
        }
    }
    
    return 0;
}
