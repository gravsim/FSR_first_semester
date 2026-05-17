#include <stdio.h>
#include <stdlib.h>


#define TABLE_SIZE 1000000
#define MAX_LENGTH 11
#define A 67


int get_index(char symbol) {
    return symbol - 'a';
}


int string_equal(char* string1, char* string2) {
    if (string1 == NULL || string2 == NULL) {
        return 0;
    }
    int i = 0;
    while (string1[i] && string2[i] && string1[i] == string2[i]) {
        i++;
    }
    return !(string1[i] && string2[i]);
}


typedef struct Node
{
    char* string;
    int length;
    struct Node* next;
} Node;


Node* List_search(Node* head, char* string) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next && !string_equal(head->string, string)) {
        head = head->next;
    }
    if (string_equal(head->string, string)) {
        return head;
    }
    return NULL;
}


int List_insert(Node** head, char* string, int length) {
    if (head == NULL || string == NULL) {
        return 2;
    }
    if (*head && List_search(*head, string) != NULL) {
        return 2;
    }
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return 1;
    }
    new_node->string = calloc(length + 1, sizeof(char));
    new_node->length = length;
    int i;
    for (i = 0; i < length + 1; i++) {
        new_node->string[i] = string[i];
    }
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return 0;
    }
    new_node->next = *head;
    *head = new_node;
    return 0;
}


int List_delete(Node** head, char* string) {
    if (head == NULL) {
        return 0;
    }
    Node* parent = NULL;
    Node* current = *head;
    while (current && !string_equal(current->string, string)) {
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
    free(current->string);
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
        free(current->string);
        free(current);
        current = next;
    }
    *head = NULL;
}


typedef struct Hash_table {
    int max_size;
    Node** values;
} Hash_table;


unsigned int Hash_function(char* string, int length) {
    unsigned int hash = 1;
    int i;
    for (i = 0; i < length; i++) {
        hash = hash * A + get_index(string[i]);
    }
    return hash % TABLE_SIZE;
}


int Table_push(Hash_table* hash_table, char* string, int length) {
    return List_insert(&hash_table->values[Hash_function(string, length)], string, length);
}


int Table_delete_value(Hash_table* hash_table, char* string, int length) {
    return List_delete(&hash_table->values[Hash_function(string, length)], string);
}


int Table_search(Hash_table* hash_table, char* string, int length) {
    Node* found = List_search(hash_table->values[Hash_function(string, length)], string);
    return found != NULL;
}


int Table_clear(Hash_table* hash_table) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        List_free(&hash_table->values[i]);
    }
    return 0;
}


int read_word(int* length, char* string) {
    if (length == NULL || string == NULL) {
        return 0;
    }
    *length = 0;
    scanf(" %c", string + *length);
    (*length)++;
    while (scanf("%c", string + *length) != EOF && string[*length] != '\n') {
        (*length)++;
    }
    (*length)--;
    return 1;
}


int main(void) {
    char command;
    Hash_table* hash_table = malloc(sizeof(Hash_table));
    hash_table->max_size = TABLE_SIZE;
    hash_table->values = calloc(hash_table->max_size, sizeof(Node*));
    int length = 0;
    char* string = calloc(MAX_LENGTH, sizeof(char));
    do {
        scanf("%c", &command);
        switch (command) {
            case '+':
                read_word(&length, string);
                Table_push(hash_table, string, length);
                break;
            case '?':
                read_word(&length, string);
                if (Table_search(hash_table, string, length)) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
                break;
            case '-':
                read_word(&length, string);
                Table_delete_value(hash_table, string, length);
                break;
            default:
                break;
        }
    } while (command != '#');
    Table_clear(hash_table);
    free(string);
    free(hash_table->values);
    free(hash_table);
    return 0;
}
