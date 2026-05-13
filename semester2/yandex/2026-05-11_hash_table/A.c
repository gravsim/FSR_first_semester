#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A 2.718281828459045235360
#define TABLE_SIZE 128
#define DEL -1

typedef struct Node
{
    int key;
    double value;
    struct Node* next;
} Node;


int List_insert(Node** head, int key, double value) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return 0;
    }
    new_node->value = value;
    new_node->next = NULL;
    new_node->key = key;
    if (!*head) {
        *head = new_node;
        return 0;
    }
    new_node->next = *head;
    *head = new_node;
    return 1;
}


Node* List_search(Node* head, int key) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next && head->key != key) {
        head = head->next;
    }
    if (head->key == key) {
        return head;
    }
    return NULL;
}


int List_delete(Node** head, int key) {
    if (head == NULL) {
        return 0;
    }
    Node* parent = NULL;
    Node* current = *head;
    while (current && current->key != key) {
        parent = current;
        current = current->next;
    }
    if (!current) {
        return 0;
    }
    if (parent) {
        parent->next = current->next;
    } else {
        *head = current->next;
    }
    free(current);
    return 1;
}


void List_free(Node **head) {
    if (head == NULL || *head == NULL) {
        return;
    }
    Node *current = *head;
    Node *next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}


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


int Table_push(Hash_table* Hash_table, int key, double value) {
    List_insert(&Hash_table->values[Hash_function(key)], key, value);
    return 0;
}


int Table_delete_value(Hash_table* Hash_table, int key) {
    return List_delete(&Hash_table->values[Hash_function(key)], key);
}


int Table_search(Hash_table* Hash_table, int key, double* value) {
    Node* found = List_search(Hash_table->values[Hash_function(key)], key);
    if (found == NULL) {
        return 0;
    }
    *value = found->value;
    return 1;
}


int Table_clear(Hash_table* Hash_table) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        List_free(&Hash_table->values[i]);
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