#include <stdio.h>
#include <stdlib.h>


#define START_SIZE 1e5
#define NO (-10)
#define DEL (-20)
#define FUNCTION_TYPE 0


typedef struct Node
{
    int key;
    double value;
} Node;


typedef struct Hash_table {
    int max_size;
    Node** values;
} Hash_table;


int Hash_function_0(int key, int i, int table_size) {
    return (key + i + table_size) % table_size;
}


int Hash_function_1(int key, int i, int table_size) {
    return (key + i + table_size) % table_size;
}


int Table_search(Hash_table* hash_table, int key, double* value, int (*Hash_function)(int, int, int)) {
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


int calculate_place(Hash_table* hash_table, int key, int* i, int* index, int (*Hash_function)(int, int, int)) {
    *i = 0;
    *index = Hash_function(key, *i, hash_table->max_size);
    while (*i < hash_table->max_size
        &&
        hash_table->values[*index]
        &&
        hash_table->values[*index]->key != NO
        &&
        hash_table->values[*index]->key != DEL
        ) {
        (*i)++;
        *index = Hash_function(key, *i, hash_table->max_size);
    }
    return 1;
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


int Table_push(Hash_table** hash_table, int key, double value, int (*Hash_function)(int, int, int)) {
    if (hash_table == NULL || (*hash_table)->values == NULL) {
        return 3;
    }
    double val = 0;
    if (Table_search(*hash_table, key, &val, Hash_function)) {
        return 2;
    }
    int i;
    int index;
    calculate_place(*hash_table, key, &i, &index, Hash_function);
    if (i >= (*hash_table)->max_size) {
        calculate_place(*hash_table, key, &i, &index, Hash_function);
    }
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return 1;
    }
    new_node->value = value;
    new_node->key = key;
    (*hash_table)->values[index] = new_node;
    return 0;
}


int Table_delete_value(Hash_table* hash_table, int key, int (*Hash_function)(int, int, int)) {
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


int main(void) {
    int command;
    int key;
    double value;
    Hash_table* hash_table = malloc(sizeof(Hash_table));
    hash_table->max_size = START_SIZE;
    hash_table->values = calloc(hash_table->max_size, sizeof(Node*));
    int (*function)(int, int, int);
    switch (FUNCTION_TYPE) {
        case 0:
            function = Hash_function_0;
            break;
        case 1:
            function = Hash_function_1;
            break;
        default:
            break;
    }
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %d %lf", &key, &value);
                printf("%d\n", Table_push(&hash_table, key, value, function));
                break;
            case 2:
                scanf(" %d", &key);
                if (Table_search(hash_table, key, &value, function)) {
                    printf("%lf\n", value);
                } else {
                    printf("Not found\n");
                }
                break;
            case 3:
                scanf(" %d", &key);
                if (Table_delete_value(hash_table, key, function)) {
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
