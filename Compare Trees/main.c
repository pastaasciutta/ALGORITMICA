#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;

node* new_elem(int key) {
    node* new = malloc(sizeof(node));
    new -> key = key;
    new -> left = NULL;
    new -> right = NULL;
    return new;
}

node* rec_insert(node* root, int key) {
    if (root == NULL) {
        return new_elem(key);
    }

    if (key > root -> key) {
        root -> right = rec_insert(root -> right, key);
    } else {
        root -> left = rec_insert(root -> left, key);
    }

    return root;
}

int max(int a, int b)
{
    return (a >= b) ? a : b;
}

// calcola altezza  sottoalbero
int height(node* node)
{
    if (node == NULL)
        return 0;

    return 1 + max(height(node->left), height(node->right));
}


int max_unbalance(node* root)
{
    int lh;
    int rh;
    int curr_max =0;
    int max =0;
    
    if (root != NULL){
      lh = height(root->left);
      rh = height(root->right);

      curr_max = abs(lh-rh);
      if(curr_max > max){
        max = curr_max;
      }
    }
    
    return max;
}

// Libero la memoria
void deallocate(node* root) {
    if (root == NULL) {
        return;
    }

    // Vado a destra e a sinistra
    deallocate(root -> right);
    deallocate(root -> left);

    // Quando arrivo al caso base ovvero quando raggiungo la fine di un sottoalbero
    // Elimino ricorsivamente bottom-up
    free(root);

}

int main() {
    int n, k;
    int elem;
    int check;
    node* root = NULL;

    // dimensione albero
    scanf("%d",&n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        root = rec_insert(root, elem);
    }

    check = max_unbalance(root);

    printf("%d\n", check);

    deallocate(root);

    return 0;
}
