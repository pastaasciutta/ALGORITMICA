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
    if (root == NULL) return new_elem(key);
    
    if (key > root -> key) {
        root -> right = rec_insert(root -> right, key);
    } else {
        root -> left = rec_insert(root -> left, key);
    }
    
    return root;
}

void deallocate(node* root) {
    if (root == NULL) return;
    
    deallocate(root -> left);
    deallocate(root -> right);
    
    free(root);
}

void nodes_at_level(node* root, int pr, int k) {
    if (root == NULL) {
        return;
    }
    if (pr == k) {
        printf("%d\n", root -> key);
        return;
    }
    
    nodes_at_level(root -> left, pr + 1, k);
    nodes_at_level(root -> right, pr + 1, k);
    
}

int main() {
    int n, elem, k;
    node* root = NULL;

    scanf("%d", &n);
    
    if (n == 0) {
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        root = rec_insert(root, elem);
    }
    
    scanf("%d", &k);
    
    nodes_at_level(root, 0, k);
    
    deallocate(root);
    
    return 0;
}

