#include <stdio.h>
#include <stdlib.h>


#define START_SIZE 1
#define NO (-10)
#define DEL (-20)


typedef struct Node
{
    int key;
    double value;
} Node;


typedef struct Hash_table {
    int max_size;
    Node** values;
} Hash_table;


int Table_expand(Hash_table* hash_table) {
    int old_size = hash_table->max_size;
    hash_table->max_size *= 2;
    Node** memory = realloc(hash_table->values, hash_table->max_size * sizeof(Node*));
    if (!memory) {
        return 0;
    }
    hash_table->values = memory;
    int i;
    for (i = old_size - 1; i < hash_table->max_size; i++) {
        hash_table->values[i] = NULL;
    }
    return 1;
}


double fraction(double a) {
    return a - (int)a;
}


int Hash_function(int key, int i, int table_size) {
    return (key + i + table_size) % table_size;
}


int Table_search(Hash_table* hash_table, int key, double* value) {
    int i = 0;
    int index = Hash_function(key, i, hash_table->max_size);
    while (i < hash_table->max_size
        &&
        hash_table->values[index]
        &&
        hash_table->values[index]->key != key
        ) {
        i++;
        index = Hash_function(key, i, hash_table->max_size);
    }
    Node* found = hash_table->values[index];
    if (i < hash_table->max_size && found && found->key == key) {
        *value = found->value;
        return 1;
    }
    return 0;
}


int calculate_place(Hash_table* hash_table, int key, int* i, int* index) {
    *i = 0;
    *index = Hash_function(key, *i, hash_table->max_size);
    while (*i < hash_table->max_size
        &&
        hash_table->values[*index]
        &&
        hash_table->values[*index]->key != NO
        ) {
        (*i)++;
        *index = Hash_function(key, *i, hash_table->max_size);
    }
    return 1;
}


int Table_push(Hash_table* hash_table, int key, double value) {
    if (hash_table == NULL || hash_table->values == NULL) {
        return 3;
    }
    double val = 0;
    if (Table_search(hash_table, key, &val)) {
        return 2;
    }
    int i;
    int index;
    calculate_place(hash_table, key, &i, &index);
    if (i >= hash_table->max_size) {
        if (!Table_expand(hash_table)) {
            return 1;
        }
        calculate_place(hash_table, key, &i, &index);
    }
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return 1;
    }
    new_node->value = value;
    new_node->key = key;
    hash_table->values[index] = new_node;
    return 0;
}


int Table_delete_value(Hash_table* hash_table, int key) {
    int i = 0;
    int index = Hash_function(key, i, hash_table->max_size);
    while (i < hash_table->max_size
        &&
        hash_table->values[index]
        &&
        hash_table->values[index]->key != key
        &&
        hash_table->values[index]->key != NO
        ) {
        i++;
        index = Hash_function(key, i, hash_table->max_size);
    }
    if (i < hash_table->max_size
        &&
        hash_table->values[index]
        &&
        hash_table->values[index]->key == key
        ) {
        Node* found = hash_table->values[Hash_function(key, i, hash_table->max_size)];
        found->key = DEL;
        return 1;
    }
    return 0;
}


int Table_clear(Hash_table* hash_table) {
    if (hash_table == NULL || hash_table->values == NULL) {
        return 1;
    }
    int i;
    for (i = 0; i < hash_table->max_size; i++) {
        if (hash_table->values[i]) {
            free(hash_table->values[i]);
            hash_table->values[i] = NULL;
        }
    }
    return 0;
}


int main(void) {
    int command;
    int key;
    double value;
    Hash_table* hash_table = malloc(sizeof(Hash_table));
    hash_table->max_size = START_SIZE;
    hash_table->values = calloc(hash_table->max_size, sizeof(Node*));
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %d %lf", &key, &value);
                printf("%d\n", Table_push(hash_table, key, value));
                break;
            case 2:
                scanf(" %d", &key);
                if (Table_search(hash_table, key, &value)) {
                    printf("%lf\n", value);
                } else {
                    printf("Not found\n");
                }
                break;
            case 3:
                scanf(" %d", &key);
                if (Table_delete_value(hash_table, key)) {
                    printf("0\n");
                } else {
                    printf("Not found\n");
                }
                break;
            case 4:
                Table_clear(hash_table);
                printf("0\n");
                break;
            default:
                break;
        }
    } while (command != 0);
    Table_clear(hash_table);
    free(hash_table->values);
    free(hash_table);
    return 0;
}
