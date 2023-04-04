#include <stdio.h>
#include <stdlib.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

// Struttura Nodo Albero
typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;

node* new_element(int key) {
    node* new = malloc(sizeof(node));
    new -> key = key;
    new -> left = NULL;
    new -> right = NULL;
    return new;
}

node* rec_insert(node* root, int key) {
    if (root == NULL) {
        return new_element(key);
    }
    
    if (key >= root -> key) {
        root -> right = rec_insert(root -> right, key);
    } else {
        root -> left = rec_insert(root -> left, key);
    }
    
    return root;
}

// Libero la memoria
void deallocate(node* root) {
    if (root == NULL) return;
    
    deallocate(root -> left);
    deallocate(root -> right);
    
    free(root);
}
/* node* find_max(node* root) {
    if (root == NULL) return NULL;

    if (root -> right == NULL) {
        return root;
    } else {
        return find_max(root -> right);
    }
} */

node* find_max(node* root) {

    if (root == NULL) return NULL;

    if (root -> right != NULL)
        return find_max(root -> right);
    return root;
}

node* second_max_value(node* root, node* parent) {
    if (root == NULL) return NULL;

    if (root -> right == NULL) {
        if (root -> left == NULL) {
            return parent;
        } else {
            return find_max(root -> left);
        }
    }

    return second_max_value(root -> right, root);
}

int main() {
    int n, elem;
    node* root = NULL;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        root = rec_insert(root, elem);
    }
    
    printf("%d\n", second_max_value(root, NULL) -> key);
    
    deallocate(root);
    
    return 0;
}