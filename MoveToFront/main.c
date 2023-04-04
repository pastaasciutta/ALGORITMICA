#include <stdio.h>
#include <stdlib.h>

typedef struct _El {
  int key;
  struct _El* next;
} EL;

void insertElementInQueue(EL** hd, int el, EL** last) {
  // Preparare l'oggetto da inserire
  EL* new = (EL *)malloc(sizeof(EL));
  new -> key = el;
  new -> next = NULL;
  // Caso in cui la lista è vuota
  // hd e last = NULL
  // caso base
  if (*last == NULL) {
    *hd = new;
    *last = new;
  } else { // caso iterativo
    (*last) -> next = new;
    *last = new;
  }
}

int searchIndex(EL** head, int el) {
  EL* p = *head;
  EL* t = NULL;
  int index = 0;

  // Casi base
  if (*head == NULL) return -1; // Va

  // Caso lista mono elemento
  if (p -> next == NULL) {  // Va
    if (p -> key == el) {
      return 0;
    } else {
      return -1;
    }
  }

   // Caso iterativo
  if (p -> key == el) { // Va
    return 0;
  }

  index = 1;

  t = p -> next; // p primo elemento; t secondo elemento

  while (t != NULL) {
    if (t -> key == el) { //
      // MTF
      p -> next = t -> next;
      t -> next = *head;
      *head = t;

      return index;
    }
    p = t;
    t = t -> next;
    index++;
  }

  return -1;
}

int main() {
  int i, n, element;
  int ind = 0;

  scanf("%d", &n);

  EL* head = NULL;
  EL* last = NULL;

  for (i = 0; i < n; i++) {
    scanf("%d", &element);
    insertElementInQueue(&head, element, &last);
  }

  i = 0;

  // Chiedo elementi da cercare
  while (1==1) {
    scanf("%d", &element);
    i = searchIndex(&head, element); // Stampo  l'indice qualunque esso sia
    printf("%d\n", i);
    if (i < 0) {
      break;
    }
    ind++;
  }
  // Elimino la lista
  EL* current = head;
  while (current != NULL) {
    current = current -> next;
    free(head);
    head = current;
  }

  return 0;
}
