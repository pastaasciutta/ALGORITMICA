/*
  CON REVERSE
 Scrivere un programma che legga da tastiera una sequenza di n interi e li inserisca in una lista nell’ordine di immissione. La lista deve essere mono- direzionale.
 Il programma deve stampare il contenuto della lista percorrendola in ordine inverso.
*/

#include <stdio.h>
#include <stdlib.h>

// Creo la struttura elemento
typedef struct _Elem{
    int info;
    struct _Elem *next;
} Elem;

// Procedura di inserimento
void insertElement(Elem** hd, int key) {
    // Preparo il nuovo elemento
    Elem *new = (Elem *)malloc(sizeof(Elem));
    new -> info = key;
    new -> next = NULL;

    // In caso di lista vuota, la testa della lista è il nuovo elemento
    if (*hd == NULL) {
        *hd = new;
    } else {
        // {Credo che il codice sprechi molto tempo qui, perchè ad ogni inserimento fa tanti cicli quanti sono gli elementi}
        // {Forse potrei cercare di salvare l'ultimo elemento, senza che ogni volta faccio il ciclo}
        // Altrimenti scorro fino all'ultimo, e inserisco l'elemento in coda
        Elem *ult = *hd;
        while (ult -> next != NULL) {
            ult = ult -> next;
        }

        ult -> next = new;
    }
}

void reverseList(Elem** hd) {
    // Se la lista è vuota oppure ha un solo elemento, ritorno.
    if (*hd == NULL || (*hd) -> next == NULL) {
        return;
    }

    // c = primo elemento lista
    // n = secondo elemento lista
    // z = (possibile) terzo elemento lista
    Elem *c = *hd;
    Elem *n = c -> next;
    Elem *z = n -> next;

    // Mando il next della testa a NULL
    c -> next = NULL;

    // Per ogni ciclo avanzo di un posto a destra c, n, z
    // Il ciclo termina quando z è NULL
    while (z != NULL) {
        // Sistemo il next di n in c (il suo precedente)
        n -> next = c;
        // Sposto c in n (un posto a dx)
        c = n;
        // Sposto n in z e z in next(un posto a dx)
        n = z;
        z = z -> next;
    }

    // Sposto il next dell'ultimo elemento e sistemo  la testa
    n -> next = c;
    *hd = n;
}

int main(int argc, const char * argv[]) {
    // Inserimento
    int n, i, x;
    scanf("%d", &n);

    Elem *head = NULL;

    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        insertElement(&head, x);
    }


    reverseList(&head);


    // Printing
    Elem *cur = head;
    while (cur != NULL) {
        printf("%d\n", cur -> info);
        cur = cur -> next;
    }

    // Garbage
    free(head);

    return 0;
}

// //SENZA REVERSE
// /*
//  Scrivere un programma che legga da tastiera una sequenza di n interi e li inserisca in una lista nell’ordine di immissione. La lista deve essere mono- direzionale.
//  Il programma deve stampare il contenuto della lista percorrendola in ordine inverso.
// */
//
// #include <stdio.h>
// #include <stdlib.h>
//
// // Creo la struttura elemento
// typedef struct _Elem{
//     int info;
//     struct _Elem *next;
// } Elem;
//
// // Procedura di inserimento
// void insertElement(Elem** hd, int key) {
//     // Preparo il nuovo elemento
//     Elem *new = (Elem *)malloc(sizeof(Elem));
//     new -> info = key;
//
//     if (*hd == NULL) {
//         new -> next = NULL;
//     } else {
//         new -> next = *hd;
//     }
//     *hd = new;
// }
//
// int main(int argc, const char * argv[]) {
//     // Inserimento
//     int n, i, x;
//     scanf("%d", &n);
//
//     Elem *head = NULL;
//
//     for (i = 0; i < n; i++) {
//         scanf("%d", &x);
//         insertElement(&head, x);
//     }
//
//     // Printing
//     Elem *cur = head;
//     while (cur != NULL) {
//         printf("%d\n", cur -> info);
//         cur = cur -> next;
//     }
//
//     // Garbage
//     free(head);
//
//     return 0;
// }
