#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
   int num;
   struct elemento* next;
}elemento;

elemento *primo (int val){

    elemento* A= (elemento*)malloc(sizeof(elemento));
    A->num = val;
    A->next = NULL;
    return A;
}

elemento *coda (elemento *last, int val){

    elemento* B = last->next = (elemento*)malloc(sizeof(elemento));
    B->num = val;
    B->next = NULL;
    return B;
}

void stampainversa (elemento *c){
    if(c->next != NULL)
        stampainversa (c->next);
    printf("%d\n", c->num);
    return;
}

int main(){

    int len;
    scanf("%d",&len);

    int n; 
    scanf("%d",&n);


    elemento *testa, *nuovo = NULL;
    testa = nuovo = primo(n);

    for(int i=len-1; i>0 ;i--){

        scanf("%d",&n);
        nuovo = coda(nuovo,n);
    }

    stampainversa(testa);

    return 0;
}