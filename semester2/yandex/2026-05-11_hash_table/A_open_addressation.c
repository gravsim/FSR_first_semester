#include <stdio.h>
#include <stdlib.h>

#define A 2.718281828459045235360
#define TABLE_SIZE 10
#define NO 10
#define DEL 10



typedef struct Node
{
    int key;
    double value;
} Node;


typedef struct Hash_table {
    int max_size;
    Node** values;
} Hash_table;


double fraction(double a) {
    return a - (int)a;
}


unsigned int Hash_function(unsigned int key) {
    return (unsigned int)(fraction(key * A) * TABLE_SIZE) % TABLE_SIZE;
}



int Table_search(Hash_table* Hash_table, int key, double* value) {
    int index = Hash_function(key);
    int i = 0;
    while (i < TABLE_SIZE && Hash_table->values[index]->key != key) {
        index = Hash_function(index);
        i++;
    }
    if (i < TABLE_SIZE && Hash_table->values[index]->key == key) {
        Node* found = Hash_table->values[Hash_function(index)];
        *value = found->value;
        return 1;
    }
    return 0;
}


int Table_push(Hash_table* Hash_table, int key, double value) {
    double val;
    if (Table_search(Hash_table, key, &val)) {
        return 2;
    }
    int index = Hash_function(key);
    while (Hash_table->values[index]->key != NO) {
        index = Hash_function(index);
    }
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return 1;
    }
    new_node->value = value;
    new_node->key = key;
    Hash_table->values[index] = new_node;
    return 0;
}


int Table_delete_value(Hash_table* Hash_table, int key) {
    int index = Hash_function(key);
    int i = 0;
    while (i < TABLE_SIZE && Hash_table->values[index]->key != key) {
        index = Hash_function(index);
        i++;
    }
    if (i < TABLE_SIZE && Hash_table->values[index]->key == key) {
        Node* found = Hash_table->values[Hash_function(index)];
        *value = found->value;
        return 1;
    }
    return 0;
}


int Table_clear(Hash_table* Hash_table) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        free(Hash_table->values[i]);
    }
    return 0;
}


int main(void) {
    int command;
    int key;
    double value;
    int status = 0;
    Hash_table* Hash_table = malloc(sizeof(Hash_table));
    Hash_table->max_size = TABLE_SIZE;
    Hash_table->values = calloc(Hash_table->max_size, sizeof(Node*));
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %d %lf", &key, &value);
                printf("%d\n", Table_push(Hash_table, key, value));
                break;
            case 2:
                scanf(" %d", &key);
                if (Table_search(Hash_table, key, &value)) {
                    printf("%lf\n", value);
                } else {
                    printf("Not found\n");
                }
                break;
            case 3:
                scanf(" %d", &key);
                if (Table_delete_value(Hash_table, key)) {
                    printf("0\n");
                } else {
                    printf("Not found\n");
                }
                break;
            case 4:
                Table_clear(Hash_table);
                printf("%d\n", status);
                break;
            default:
                break;
        }
    } while (command != 0);
    free(Hash_table->values);
    free(Hash_table);
    return 0;
}
