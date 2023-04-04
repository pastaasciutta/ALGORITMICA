#include <stdio.h>
#include <stdlib.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;

node* new_element(int value) {
    node* new = malloc(sizeof(node));
    new -> key = value;
    new -> left = NULL;
    new -> right = NULL;
    
    return new;
}

node* rec_insert(node* root, int elem) {
    if (root == NULL) {
        return new_element(elem);
    }
    
    if (elem > root -> key) {
        root -> right = rec_insert(root -> right, elem);
    } else {
        root -> left = rec_insert(root -> left, elem);
    }
    
    return root;
}

void deallocate(node* root) {
    if (root == NULL) {
        return;
    }
    
    deallocate(root -> left);
    deallocate(root -> right);
    
    free(root);
}

int LCS(node* root, int x, int y) {
    
    if (root -> key == x) {
        return x;
    }
    
    if (root -> key == y) {
        return y;
    }
    
    if ((x < root -> key && y > root -> key) || (x > root -> key && y < root -> key)) {
        return root -> key;
    }
    
    int result = 0;
    
    if (x < root -> key && y < root -> key) {
        result = LCS(root -> left, x, y);
    } else {
        result = LCS(root -> right, x, y);
    }
    
    if (result != 0) {
        return result;
    } else {
        return 0;
    }
    
}

int main() {
    int n, elem;
    int x, y;
    node* root = NULL;
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        root = rec_insert(root, elem);
    }
    
    scanf("%d", &x);
    scanf("%d", &y);
    
    printf("%d\n", LCS(root, x, y));
    
    deallocate(root);
    
    return 0;
}
