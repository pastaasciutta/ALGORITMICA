#include <stdio.h>
#include <stdlib.h>

typedef struct n{
    int val;
    struct n *next;
    struct n *prec;
} num;

num *push_tail(num *ex_tail, int a);
void rev_print(num *tail);

int main(){
    int len;
    scanf("%d",&len);
    int nbr;
    num *head, *tail = NULL;

    for(int i=len; i>0; i--){
        scanf("%d",&nbr);
        tail = push_tail(tail, nbr);
        if (i==len)
            head=tail;
    }
    rev_print(tail);
}

num *push_tail(num *ex_tail, int a){
    num *new = (num*)malloc(sizeof(num));
    ex_tail->next= new;
    new->prec = ex_tail;
    new->val = a;
    new->next = NULL;
    return new;
}

void rev_print(num *tail){
    while(tail->prec != NULL){
        printf("%d\n",tail->val);
        tail = tail->prec;
        free(tail->next);
    }
    printf("%d\n",tail->val);
    free(tail);
    return;
}