#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* center;
    struct _node* right;
} node;

node* new_elem(int key) {
    node* new = malloc(sizeof(node));
    new -> key = key;
    new -> left = NULL;
    new -> center = NULL;
    new -> right = NULL;
    
    return new;
}

node* rec_insert_ternary(node* root, int key) {
    if (root == NULL) {
        return new_elem(key);
    }
    
    if (key < root -> key) {
        root -> left = rec_insert_ternary(root -> left, key);
    } else if (key % root -> key == 0) {
        root -> center = rec_insert_ternary(root -> center, key);
    } else {
        root -> right = rec_insert_ternary(root -> right, key);
    }
    
    return root;
}

int n_node_son(node* root) {
    // Casi base
    if (root == NULL) {
        return 0;
    }
    
    int lx = n_node_son(root -> left);
    int cx = n_node_son(root -> center);
    int rx = n_node_son(root -> right);
    
    if (root -> left != NULL && root -> center != NULL && root -> right != NULL) {
        return lx + cx + rx + 1;
    } else {
        return lx + cx + rx;
    }
    
}

void deallocate(node* root) {
    if (root == NULL) {
        return;
    }
    
    deallocate(root -> left);
    deallocate(root -> center);
    deallocate(root -> right);
    
    free(root);
}

int main() {
    int n, elem;
    node* root = NULL;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        root = rec_insert_ternary(root, elem);
    }
    
    printf("%d\n", n_node_son(root));
    
    deallocate(root);
    
    return 0;
}

