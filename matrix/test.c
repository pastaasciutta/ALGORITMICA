#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void makeMatrix(int val, int m[val][val]);
int maxColValue(int val, int m[val][val]);
bool checkZeros(int val, int m[val][val]);
void printMatrix(int val, int m[val][val]);
bool isSymmetric(int val,int mat[val][val]);
void transpose(int val,int mat[val][val], int tr[val][val]);

int main(){

    int n =0;
    printf("inserisci la dimensione: ");
    scanf("%d",&n);
    int mat[n][n];
    // creo la matrice
    makeMatrix(n,mat);
    
    /* se la matrice è simmetrica
    controllo che ci siano solo 0 in diagonale
    se è vero allora stampo la colona con la somma massima
    */

    if(isSymmetric(n,mat)) {
            if(checkZeros(n,mat)){
                printf("colonna con la somma maggiore alla posizione: %d",maxColValue(n,mat));
            }else{
                printf("la matrice non ha zeri in diagonale");
                // exit failure
                exit (1);
            }
    }else{
        puts("la mattrice non è simmetrica");
        exit (1);
    }

    return 0;
}

void makeMatrix(int val, int m[val][val]){
    size_t i =0;
    char* input = malloc(20*sizeof(char));
    while(i<val){
        printf("inserisci i valori da immettere in matrice: ");
        scanf("%s",input);
        for(size_t j =0;j<val;j++) m[i][j] = input[j]-'0';
        i++;
    }
    free(input);
}

int maxColValue(int val, int m[val][val]){
    int max=0;
    int temp =0;
    int rem =0;
    for(size_t j=0;j<val;j++){
        for(size_t i=0;i<val;i++){
        temp += m[i][j];
    }
    printf("%d",temp);
    if(temp > max){
        max=temp;
        rem = j;
    }
    }

    return rem;
}

bool checkZeros(int val, int m[val][val]){
    for(size_t i=0;i<val;i++)
        if(m[i][i] !=0) return false;
    return true;
}

void printMatrix(int val, int m[val][val])
{
    printf("Matrix is \n");
    for (size_t i = 0; i < val; i++) {
        for (size_t j = 0; j < val; j++) {
            printf("\t%d\t", m[i][j]);
        }
        printf("\n");
    }
}


void transpose(int val,int mat[val][val], int tr[val][val])
{
    for (int i = 0; i < val; i++)
        for (int j = 0; j < val; j++)
            tr[i][j] = mat[j][i];
}

bool isSymmetric(int val,int mat[val][val])
{
    int tr[val][val];
    transpose(val,mat, tr);
    for (int i = 0; i < val; i++)
        for (int j = 0; j < val; j++)
            if (mat[i][j] != tr[i][j])
                return false;
    return true;
}
