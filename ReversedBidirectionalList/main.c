#include <stdio.h>
#include <stdlib.h>

typedef struct El {
  int info;
  struct El* prev;
  struct El* next;
} EL;

void insertHead(EL** hd, int key) {
  // Prepare new element
  EL* new = (EL *)malloc(sizeof(EL));
  new -> info = key;
  new -> prev = NULL;
  new -> next = *hd;

  if (*hd != NULL) {
    (*hd) -> prev = new;
  }

  *hd = new;
}

int main() {
  int i, n, element;
  scanf("%d", &n);

  EL* head = NULL;

  for (i = 0; i < n; i++) {
    scanf("%d", &element);
    insertHead(&head, element);
  }

  EL* current = head;
  while (current != NULL) {
    printf("%d\n", current -> info);
    current = current -> next;
  }

  //current = head;
  // while (current -> next != NULL) {
  //   current = current -> next;
  //   free(current -> prev);
  // }
  //
  // free(current);

  return 0;
}
