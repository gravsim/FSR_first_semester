#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A 2.718281828459045235360
#define table_size 128
#define DEL -1

struct Node
{
    int value;
    struct Node* next;
};


int insert(struct Node** head_pp, int value) {
    struct Node* new_node = malloc(sizeof(struct Node));
    if (!new_node) return -2;
    new_node->value = value;
    new_node->next = NULL;
    if (!*head_pp) {
        *head_pp = new_node;
        return 0;
    }
    new_node->next = *head_pp;
    *head_pp = new_node;
    return 0;
}


struct Hash_table {
    int size;
    int max_size;
    double* values;
};


double fraction(double a) {
    return a - (int)a;
}


unsigned int Hash_function(unsigned int key) {
    return (unsigned int)(fraction(key * A) * table_size) % table_size;
}


int Table_push(struct Hash_table* Hash_table, int key, double value) {
    Hash_table->values[Hash_function(key)] = value;
    return 0;
}


int Table_pop(struct Hash_table* Hash_table, int key, double* value) {
    *value = Hash_table->values[Hash_function(key)];
    Hash_table->values[Hash_function(key)] = DEL;
    return 0;
}


int Table_top(struct Hash_table* Hash_table, int key, double* value) {
    *value = Hash_table->values[Hash_function(key)];
    return 0;
}


int Table_is_empty(struct Hash_table* Hash_table, int* value) {
    *value = !Hash_table->size;
    return 0;
}


int Table_clear(struct Hash_table* Hash_table) {
    Hash_table->size = 0;
    return 0;
}


int Table_check(struct Hash_table* Hash_table) {
    int status;
    Table_is_empty(Hash_table, &status);
    if (status) {
        printf("Hash_table is empty\n");
    }
    return !status;
}


int main(void) {
    int command;
    int key;
    double value;
    int status;
    struct Hash_table* Hash_table = malloc(sizeof(struct Hash_table));
    Hash_table->size = 0;
    Hash_table->max_size = 100;
    Hash_table->values = (double*)calloc(Hash_table->max_size, sizeof(double));
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %d %lf", &key, &value);
                Table_push(Hash_table, key, value);
                break;
            case 2:
                if (Table_check(Hash_table)) {
                    Table_pop(Hash_table, key, &value);
                }
                break;
            case 3:
                if (Table_check(Hash_table)) {
                    Table_top(Hash_table, key, &value);
                    printf("%lf\n", value);
                }
                break;
            case 4:
                Table_is_empty(Hash_table, &status);
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