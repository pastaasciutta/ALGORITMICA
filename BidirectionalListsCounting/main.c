#include <stdio.h>
#include <stdlib.h>

typedef struct _El {
  int info;
  int counter;
  struct _El* prev;
  struct _El* next;
} EL;

void insertElement(EL **hd, int el, EL **lst) {
  // Prepare new element
  EL* new = (EL *)malloc(sizeof(EL));
  new -> next = NULL;
  new -> counter = 0;
  new -> info = el;

  if (*hd == NULL) {
    new -> prev = NULL;
    *hd = new;
  } else {
    (*lst) -> next = new;
    new -> prev = *lst;
  }

  *lst = new;
}

void searchAndCount(EL** hd) {
  while (0 == 0) {
    int key;
    int index = 0;
    EL* c = *hd;
    scanf("%d", &key);

    while (c != NULL) {
      if (c -> info == key) {
        printf("%d\n", index);
        break;
      }

      index++;
      c = c -> next;
    }

    // Caso in cui l'elemento non è stato trovato
    if (c == NULL) {
      printf("-1\n");
      return;
    }

    // Caso in cui è stato trovato e la lista è composta da un solo elemento
    if ((*hd) -> next == NULL) {
      return;
    }

    // Altrimenti devo fare delle mosse...
    EL* p = (*hd) -> next;
    EL* pre = c -> prev;

    (c -> counter)++;

    if (pre != NULL) {
      // Se l'elemento precedente è stato ricercato meno volte dell'elemento
      // Puntato da c
      if (pre -> counter < c -> counter) {
        if ((*hd) -> counter < c -> counter) {
          // Sposto in testa l'elemento puntato da c
          pre -> next = c -> next;
          if (c -> next != NULL) {
            c -> next -> prev = pre;
          }
          c -> prev = NULL;
          c -> next = *hd;
          (*hd) -> prev = c;
          *hd = c;
        } else {
          int isOk = 0;
          while (p != c && !isOk) {
            if (p -> counter < c -> counter) {
              // Faccio lo spostamento
              pre -> next = c -> next;
              if (c -> next != NULL) {
                c -> next -> prev = pre;
              }
              c -> prev = p -> prev;
              p -> prev = c;
              c -> next = p;
              c -> prev -> next = c;

              isOk = 1;
            } else {
              p = p -> next;
            }
          }
        }
      }
    }

  }
}

int main() {
  int i, n, element;
  scanf("%d", &n);

  EL* head = NULL;
  EL* last = NULL;

  for (i = 0; i < n; i++) {
    scanf("%d", &element);
    insertElement(&head, element, &last);
  }

  EL* current = head;
  while (current != NULL) {
    current = current -> next;
  }

  searchAndCount(&head);

  current = head;
  while (current -> next != NULL) {
    current = current -> next;
    free(current -> prev);
  }

  free(current);

  return 0;
}
