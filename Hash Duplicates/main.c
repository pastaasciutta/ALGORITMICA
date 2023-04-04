#include <stdio.h>
#include <stdlib.h>

// Function that returns max of two elements
#define max(x, y) ((x) > (y) ? (x) : (y))

// Single monodirectional list node
typedef struct _node {
     int key;
     struct _node* next;
} node;

// List composed by nodes
typedef struct {
     node* head;
     node* last;
     size_t size;
} list;

// Hash table composed by lists
typedef struct {
     size_t a, b, p;
     size_t size; // number of lists in table
     list* buckets; // list pointer
     size_t max_bucket_size;
     size_t num_conflicts;
     size_t num_distinct_elements;
} hashtable;

// Add in queue
void list_append(list* l, int key) {
     node* new =  malloc(sizeof(node));
     new -> key = key;
     new -> next = NULL;

     // If list is empty
     if (l -> size == 0) {
          l -> head  = new;
     } else {
          l -> last -> next = new;
     }

     l -> last = new;
     l -> size++;
}

// Hash function
size_t hash(const hashtable* table, int key) {
     return ((table -> a * key + table  -> b) % table -> p) % table -> size;
}

// Init hashtable
void hashtable_init(hashtable* table, size_t size, size_t a, size_t b) {
     table -> a = a;
     table -> b  = b;
     table -> size = size;
     table -> p = 999149;
     table -> max_bucket_size = 0;
     table -> num_conflicts = 0;
     table -> num_distinct_elements = 0;

     table -> buckets = malloc(size * sizeof(list));

     for (size_t i = 0; i < size; i++) {
          table -> buckets[i].head = NULL;
          table -> buckets[i].last = NULL;
          table -> buckets[i].size = 0;
     }
}

/*void hashtable_insert(hashtable* table, int key) {
     size_t h = hash(table, key);

     if (table -> buckets[h].head == NULL) {
          list_append(&table -> buckets[h], key);
          table -> max_bucket_size = max(table -> max_bucket_size, table -> buckets[h].size);
          table -> num_distinct_elements++;
          return;
     }

     // If the first element is the element we want to insert
     // then there is a duplicate so we do not insert the current element
     if ((table -> buckets[h].head -> key) == key) {
          return;
     } else {
          node* current = table -> buckets[h].head;
          while (current != NULL) {
               if (current -> key == key) {
                    return;
               }
               current = current -> next;
          }

          list_append(&table -> buckets[h], key);
          table -> max_bucket_size = max(table -> max_bucket_size, table -> buckets[h].size);
          table -> num_distinct_elements++;

          if (table -> buckets[h].size != 1) {
               table -> num_conflicts++;
          }
     }
}*/

void hashtable_insert(hashtable* table, int key) {
     size_t h = hash(table, key);

     if (table -> buckets[h].head != NULL) {
          node* current = table -> buckets[h].head;
          while (current != NULL) {
               if (current -> key == key) {
                    return;
               }
               current = current -> next;
          }
     }

     list_append(&table -> buckets[h], key);
     table -> max_bucket_size = max(table -> max_bucket_size, table -> buckets[h].size);
     table -> num_distinct_elements++;

     if (table -> buckets[h].size != 1)
          table -> num_conflicts++;
}

int main(int argc, char* argv[]) {
     
     size_t n, a, b;
     int k;

     scanf("%lu %lu %lu", &n, &a, &b);

     hashtable table;

     hashtable_init(&table, 2*n, a, b);

     for (size_t i = 0; i < n; i++) {
          scanf("%d", &k);
          hashtable_insert(&table, k);
     }

     printf("%lu\n", table.num_conflicts);
     printf("%lu\n", table.max_bucket_size);
     printf("%lu\n", table.num_distinct_elements);
}
