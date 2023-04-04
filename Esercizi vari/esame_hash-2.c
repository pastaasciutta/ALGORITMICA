#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct object{
  char* name;
  int value;
  struct object* next;
} Object;

typedef struct {
    char *final_name;
    int val;
} Exam;

unsigned int hash(char* line,int mod);
Object *newNode(char* str, int num);
void addToList(Object **list, char* nam,int position);
void print_catalogue(Object *current);
short isCollision(Object *list, char* nom,int num);
short check(char* nom1, char* nom2, int num1, int num2);
int compare_list(const void* a, const void* b);
void printArray(Exam array[], int size);
void copy_to_vector(Object **tables,Object **output,int dim);

int main(){
  int n=0,new_val=0;
  unsigned int temp =0;
  // inserisci il numero di oggetti da processare
  while((scanf("%d",&n) !=1) || n<0 || n>30){
    printf("errore nell'input");
    scanf("%*[^\n]%*1[\n]");
  }

  // creo tabella hash dimensione 2N
  Object **table = (Object**) malloc(2 * n * sizeof(Object*));
  Object **table2 = (Object**) malloc(10 * n * sizeof(Object*));
  // inizialzzo l'Array
    for(short i=0;i<2*n;i++){
      table[i] = NULL;
    }

  char* new_name = (char*) malloc(101*sizeof(char));
  for(short i=0;i<n;i++){
    scanf("%s", new_name);
    scanf("%d",&new_val);
    temp = hash(new_name,n);
    addToList(&table[temp], new_name, new_val);
    temp=0;
  }

  copy_to_vector(table,table2,10*n);

qsort(table2,10*n,sizeof(Object*),compare_list);

for(short i=0;i<2*n;i++){
    if(table2[i]) print_catalogue(table[i]);
  }
return 0;

}

void copy_to_vector(Object **tables,Object **output,int dim){

  size_t j = 0;

      for(size_t i = 0; i < dim; i++) {
          if(tables[i] != NULL) {
              output[j++] = tables[i];

              Object *nextChild = tables[i]->next;
              while(nextChild != NULL) { // copy all the nodes of the list in the i-th position of the original array
                  output[j++] = nextChild;
                  nextChild = nextChild->next;
              }
          }
      }
}

void printArray(Exam array[], int size){
  for(short i=0; i<size; i++)
        printf("%s\n",array[i].final_name);
}


// inserico nella lista data dalla posizione hash in ordine
// lessicografico non decrescente
void addToList(Object **list, char *nom, int num) {
	Object *curr = *list, *prev = 0;
	Object *n = newNode(nom, num);
	short flag = isCollision(curr,nom,num);
	if(n) {
		while(curr !=NULL && check(curr->name,nom,curr->value,num)>0) {
			prev = curr;
			curr = curr->next;
		}
		if(prev) {
			// non sono in testa
      if(flag==3){
        // faccio lo swap come richiesto
        prev->value=num;
      } else{
        prev->next = n;
        n->next = curr;
      }
		}
		else if(flag==0) {
			// inserisco in testa
			n->next = *list;
			*list = n;
		}else{
      // Non fare nulla come richiesto
    }
	}
	else {
		puts("impossibile allocare");
		exit(1);
	}
}

  void print_catalogue(Object *current) {
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}

short check(char* nom1, char* nom2, int num1, int num2) {
    if (strcmp(nom1, nom2) > 0) {//Ordina per nome
      if(num1<num2){
        return 1;
      }else if(num1>num2){
        return 1;
      } else{
        return 0;
      }
    } else if (strcmp(nom1, nom2) < 0){
      if(num1<num2){
        return 1;
      }else if (num1>num2){
        return 1;
      }else{
        return 0;
      }
    }
    return -1;
}

Object* newNode(char *str, int num) {
	Object *node = (Object*) malloc(sizeof(Object));
	if(node) {
		node->name = (char*) malloc((strlen(str) + 1) * sizeof(char));
	 	node->value = num;
		strcpy(node->name, str);
		node->next = NULL;
		return node;
	}
	return NULL;
}

int compare_list(const void* a, const void* b) {
  // type casting dei puntatori
   Object *t1= *(Object**)a;
   Object *t2= *(Object**)b;

   if(t1 != NULL && t2 !=NULL){
   if(strcmp(t1->name,t2->name)<0 || strcmp(t1->name,t2->name)>0){
     if(t1->value > t2->value){
       return (t2->value - t1->value);
     }else if(t1->value == t2->value){
       return strcmp(t1->name,t2->name);
     }else{
       return strcmp(t2->name,t1->name);
     }
   }
 }
 }


short isCollision(Object *head, char* get_name,int p) {

  if (head == NULL) {
    return 0; //non c'è stata collisione
  }else if(head->value==p){  //c'è collisione
    return 1;
  }else if ((strcmp(head->name,get_name)==0) && (p<= head->value)) {
      return 2;
    }else if ((strcmp(head->name,get_name)==0) && (p>head->value)) {
        return 3;
      }
    else {
      isCollision(head->next, head->name,p); //continua a scorrere la lista
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
