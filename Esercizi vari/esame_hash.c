#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct phonebook{
    char name[50];
    char number[20];
    unsigned int pos;
    struct phonebook* next;
} Phonebook;

typedef Phonebook* ptr;

unsigned int hash(char line[],int mod);
void addToList(ptr* head_ref, char nam[],char num[],unsigned int position);
short check(char* nom1, char* nom2, char* num1, char* num2);
short isCollision(ptr head, unsigned int p);
void print_catalogue(ptr* current,unsigned int p);

int main(){
  ptr element = NULL;
  char lin[50];
  char numb[20];
  int n =0;
  unsigned int k=0;
  // numero di elelemtni da aggiungere
  while((scanf("%d",&n)!=1) || n<0){
    printf("errore nell'input\n");
    scanf("%*[^\n]%*1[\n]");
  }
  unsigned int tmp=0;
  // chiedo in input il nome e il numero della persona da aggiungere in rubrica
  for(short i=0;i<n;i++){
    scanf("%s",&lin);
    scanf("%s", &numb);
    tmp=hash(lin,n);
    addToList(&element,lin,numb,tmp);
  }

  // numero di poszione scelto
  while((scanf("%u",&k)!=1) || k<0 || k>2*n ){
    printf("errore nell'input\n");
    scanf("%*[^\n]%*1[\n]");
  }

  print_catalogue(&element,k);

  return 0;
}

void addToList(ptr* head_ref, char nam[],char num[],unsigned int position) {
    //il seguente ciclo scorre la lista di libri finché non raggiunge la posizione giusta per mantenere la lista ordinata
    ptr curr = *head_ref;
    ptr prec = NULL;
    if(isCollision(prec,position)==1){
    while (curr != NULL && check(nam, curr->name, num, curr->number) > 0) {
        prec = curr;
        curr = curr->next;
    }
  }

    //inserisco l'elemento  solo se non e' già presente nella lista
    if (curr == NULL || strcmp(curr->number, num)!=0) {
        ptr new_ref = malloc(sizeof(Phonebook)); //alloco memoria per un nuovo elemento della lista
        if (new_ref != NULL) { //l'allocazione e' riuscita
            //inizializzo il nuovo elemento
            strcpy(new_ref->number,num);
            strcpy(new_ref->name,nam);
            new_ref->pos = position;
            new_ref->next = curr;
        }
        if (prec == NULL) {
            *head_ref = new_ref; //inserisco in testa
        }
        else {
            prec->next = new_ref; //inserisco tra prec e curr
        }
    }
  }

  short check(char* nom1, char* nom2, char* num1, char* num2) {
      if (strcmp(nom1, nom2) > 0) { //Ordina per nome
          return 1;
      }
      else if (strcmp(nom1, nom2) == 0) { //Se il nome è lo stesso, si guarda il numero
          if (strcmp(num1,num2)>0) {
              return 1;
          }
          else if (strcmp(nom1, nom2) == 0) {
            if(strcmp(num1,num2)==0){
              return 0;
            }
              return 0;
          }
      }
      return -1;
  }

  short isCollision(ptr head, unsigned int p) {
  	if (head == NULL) {
  		return 0; //c'è stat collisione
  	}
  	else {
  	    if (head->pos==p) { //non c'è collisione
  			return 1;
  		}
  		else {
  			isCollision(head->next, p); //continua a scorrere la lista
  		}
  	}
  }

  // stampa tutto il catalogo
    void print_catalogue(ptr* current,unsigned int p) {
      while ((*current != NULL)) {
        if((*current)->pos==p){
          printf("%s %s\n", (*current)->name,(*current)->number);
          *current = (*current)->next;
        }else{
          *current = (*current)->next;
        }
      }
  }

  unsigned int hash(char* line,int mod){
    unsigned int sum =0;
    // bisogna evitare il carattere end line \0
    for (short i=0;i<strlen(line);i++){
      sum += (unsigned int)line[i];
    }
    return (sum) % (2*mod);
  }
