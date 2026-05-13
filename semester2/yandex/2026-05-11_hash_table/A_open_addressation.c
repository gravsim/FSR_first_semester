#include <stdio.h>
#include <stdlib.h>


#define TABLE_SIZE 10
#define NO (-10)
#define DEL (-20)



typedef struct Node
{
    unsigned int key;
    double value;
} Node;


typedef struct Hash_table {
    int max_size;
    Node** values;
} Hash_table;


double fraction(double a) {
    return a - (int)a;
}


unsigned int Hash_function(unsigned int key, unsigned int i) {
    return (key + i) % TABLE_SIZE;
}


int Table_search(Hash_table* hash_table, unsigned int key, double* value) {
    int i = 0;
    unsigned int index = Hash_function(key, i);
    while (i < TABLE_SIZE && hash_table->values[index] && hash_table->values[index]->key != key) {
        i++;
        index = Hash_function(key, i);
    }
    Node* found = hash_table->values[index];
    if (i < TABLE_SIZE && found && found->key == key) {
        *value = found->value;

        return 1;
    }
    return 0;
}


int Table_push(Hash_table* hash_table, unsigned int key, double value) {
    double val = 0;
    if (Table_search(hash_table, key, &val)) {
        return 2;
    }
    int i = 0;
    unsigned int index = Hash_function(key, i);

    while (i < TABLE_SIZE && hash_table->values[index] && hash_table->values[index]->key != NO) {
        i++;
        index = Hash_function(key, i);
    }
    if (i >= TABLE_SIZE) {
        return 3;
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


int Table_delete_value(Hash_table* hash_table, unsigned int key) {
    int i = 0;
    unsigned int index = Hash_function(key, i);
    while (i < TABLE_SIZE && hash_table->values[index] && hash_table->values[index]->key != key) {
        i++;
        index = Hash_function(key, i);
    }
    if (i < TABLE_SIZE && hash_table->values[index] && hash_table->values[index]->key == key) {
        Node* found = hash_table->values[Hash_function(key, i)];
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
    for (i = 0; i < TABLE_SIZE; i++) {

        if (hash_table->values[i]) {
            hash_table->values[i]->key = NO;
        }
    }
    return 0;
}


int main(void) {
    int command;
    int key;
    double value;
    int status = 0;
    Hash_table* hash_table = malloc(sizeof(Hash_table));
    hash_table->max_size = TABLE_SIZE;
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
                printf("%d\n", status);
                break;
            default:
                break;
        }
    } while (command != 0);
    free(hash_table->values);
    free(hash_table);
    return 0;
}
