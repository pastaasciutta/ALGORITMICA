#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sigla[100];
    int crediti;
    int grado;
} Exam;


void printArray(Exam array[], int size);
int compare_exams(const void*a, const void*b);

int main(){

  char sigla[100];
  int n=0;
  int k=0;
  int crediti=0;
  int grado=0;

  // crediti da raggiungere
  while((scanf("%d",&k)!=1) || k<0){
    printf("erroe nell'input\n");
    scanf("%*[^\n]%*1[\n]");
  }
  // esami possibili
  while((scanf("%d",&n)!=1) || n<0){
    printf("erroe nell'input");
    scanf("%*[^\n]%*1[\n]");
  }
  int check =0;
  // array di esami dimensione n
  Exam exam_list[n];
  // inserimento esami
  for(short j=0;j<n;j++){
    // se non si raggiungono i crediti massimi allora si può fare un altro inserimento
    if(crediti<k){
    scanf("%s", exam_list[j].sigla);
    scanf("%d",&exam_list[j].crediti);
    scanf("%d",&exam_list[j].grado);
    check=check+exam_list[j].crediti;
  }else{
    // veranno ignorati i prossimi inserimenti
    continue;
  }
}
qsort(exam_list,n,sizeof(Exam),compare_exams);
printArray(exam_list,n);
return 0;
}

int compare_exams(const void*a, const void*b)
{

  Exam *e1 = (Exam*)a;
  Exam *e2 = (Exam*)b;

    if (strcmp(e1->sigla, e2->sigla) < 0) {
        return -1;
    } else if (strcmp(e1->sigla, e2->sigla) > 0) {
        return 1;
    } else if (e1->crediti < e2->crediti) {
        return -1;
    } else if (e1->crediti > e2->crediti) {
        return 1;
    } else if (e1->grado < e2->grado) {
        return -1;
    } else if (e1->grado > e2->grado) {
        return 1;
    } else {
        return 0;
    }
}

void printArray(Exam array[], int size){
  for(short i=0; i<size; i++)
        printf("%s\n",array[i].sigla);
}
