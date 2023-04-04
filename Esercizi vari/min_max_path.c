#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} node;

node *tree_insert(node *root, int k) {
    if (root == NULL) {
        node *new = (node *) malloc(sizeof(node));
        new->key = k;
        new->left = NULL;
        new->right = NULL;
        return new;
    }

    if (k < root->key) {
        root->left = tree_insert(root->left, k);
    } else {
        root->right = tree_insert(root->right, k);
    }
    return root;
}

void tree_free(node *root) {
    if (root == NULL)
        return;

    tree_free(root->left);
    tree_free(root->right);
    free(root);
}

/**
 * L'algoritmo fa una visita di tipo postorder ricorsiva, accumulando la somma
 * del percorso e il minimo dopo aver effettuato le chiamate ricorsive.
 * Se l'albero è vuoto restituisce zero sia per la somma, sia per il minimo.
 * Gli indirizzi puntati da min_key e sum saranno popolati con i risultati.
 */
void min_max_path(node* root, int *min_key, int *sum) {
    // Caso base della ricorsione, restituiamo zero.
    // Attenzione: potremmo usare le foglie come caso base, ma questo
    // richiederebbe comunque di gestire il caso di un albero vuoto e più
    // istruzioni condizionali nei passi ricorsivi.
    if (root == NULL) {
        *sum = 0;
        *min_key = 0;
        return;
    }

    // Allocazione dello spazio per i risultati e visita postorder
    int left_min, right_min;
    int left_sum, right_sum;
    min_max_path(root->left, &left_min, &left_sum);
    min_max_path(root->right, &right_min, &right_sum);

    // Caso in cui il ramo sinistro ha un percorso maggiore o uguale a quello destro
    if (left_sum >= right_sum) {
        *sum = left_sum + root->key;
        // In generale, per l'invariante degli ABR il figlio sinistro di un
        // vertice è più piccolo del vertice stesso, ma nel caso in cui i due percorsi
        // siano uguali e non c'è alcun ramo sinistro non possiamo restituire left_min,
        // ma dobbiamo restituire la radice senza figlio sinistro.
        *min_key = root->left != NULL ? left_min : root->key;
    } else {
        *sum = right_sum + root->key;
        // In generale, per l'invariante degli ABR il figlio destro di un vertice è
        // più grande del vertice stesso, quindi restituiamo sempre il vertice.
        *min_key = root->key;
    }
}

int main(int argc, const char* argv[]) {
    node *root = NULL;
    size_t n;
    scanf("%zu", &n);

    for (size_t i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        root = tree_insert(root, k);
    }

    // Anche se alla fine della chiamata non utilizziamo sum, è comunque necessario
    // allocare lo spazio per il corretto funzionamento della funzione ricorsiva.
    int min_key, sum;
    min_max_path(root, &min_key, &sum);

    printf("%d\n", min_key);

    tree_free(root);

    return 0;
}
