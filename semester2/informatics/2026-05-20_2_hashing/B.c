#include <stdio.h>
#include <stdlib.h>


#define TABLE_SIZE 100000
#define MAX_LENGTH 17
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
    char latin[MAX_LENGTH];
    char** english;
    int size;
    int max_size;
    struct Node* next;
} Node;


Node* List_search(Node* head, char* string) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next && !string_equal(head->latin, string)) {
        head = head->next;
    }
    if (string_equal(head->latin, string)) {
        return head;
    }
    return NULL;
}


int copy_string(char* place, char* string, int length) {
    if (string == NULL || place == NULL) {
        return 0;
    }
    int i;
    for (i = 0; i < length; i++) {
        place[i] = string[i];
    }
    return 1;
}


int List_insert(Node** head, char* latin, char* english, int length) {
    if (head == NULL || latin == NULL) {
        return 2;
    }
    Node* node;
    if (*head) {
        node = List_search(*head, latin);
        if (node != NULL) {
            node->english[node->size] = calloc(MAX_LENGTH, sizeof(char));
            copy_string(node->english[node->size++], english, length);
            return 2;
        }
    }
    node = malloc(sizeof(Node));
    node->size = 0;
    node->max_size = 10;
    node->english = calloc(node->max_size, sizeof(char*));
    if (!node) {
        return 1;
    }
    copy_string(node->latin, latin, length);
    node->english[node->size] = calloc(MAX_LENGTH, sizeof(char));
    copy_string(node->english[node->size++], english, length);
    if (*head == NULL) {
        node->next = NULL;
        *head = node;
        return 0;
    }
    node->next = *head;
    *head = node;
    return 0;
}


void List_free(Node **head) {
    if (head == NULL || *head == NULL) {
        return;
    }
    Node *current = *head;
    Node *next;
    while (current) {
        next = current->next;
        free(current->english);
        free(current);
        current = next;
    }
    *head = NULL;
}


typedef struct Hash_table {
    int max_size;
    Node** values;
} Hash_table;


unsigned int Hash_function(char* string) {
    unsigned int hash = 1;
    int i = 0;
    while (string[i]) {
        hash = hash * A + get_index(string[i]);
        i++;
    }
    return hash % TABLE_SIZE;
}


int Table_push(Hash_table* hash_table, char* latin, char* english, int length) {
    return List_insert(&hash_table->values[Hash_function(latin)], latin, english, length);
}


int Table_search(Hash_table* hash_table, char* string) {
    Node* found = List_search(hash_table->values[Hash_function(string)], string);
    return found != NULL;
}


int Table_clear(Hash_table* hash_table) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        List_free(&hash_table->values[i]);
    }
    return 0;
}


int read_english(int* length, char* english) {
    if (length == NULL || english == NULL) {
        return 0;
    }
    *length = 0;
    scanf(" %c", english + *length);
    (*length)++;
    while (scanf("%c", english + *length) != EOF && english[*length] != '-') {
        (*length)++;
    }
    (*length)--;
    return 1;
}


int read_latin(int* length, char* latin) {
    if (length == NULL || latin == NULL) {
        return 0;
    }
    *length = 0;
    scanf(" %c", latin + *length);
    (*length)++;
    while (scanf("%c", latin + *length) != EOF && latin[*length] != '\n' && latin[*length] != ',') {
        (*length)++;
    }
    if (latin[*length] == ',') {
        (*length)--;
        return 1;
    }
    (*length)--;
    return 0;
}


int main(void) {
    int words_amount;
    Hash_table* hash_table = malloc(sizeof(Hash_table));
    hash_table->max_size = TABLE_SIZE;
    hash_table->values = calloc(hash_table->max_size, sizeof(Node*));
    int length = 0;
    char latin[MAX_LENGTH];
    char english[MAX_LENGTH];
    int i;
    int j;
    scanf("%d", &words_amount);
    int result;
    for (i = 0; i < words_amount; i++) {
        read_english(&length, english);
        do {
            result = read_latin(&length, latin);
            // printf("%s\n", latin);
            Table_push(hash_table, latin, english, length);
            printf("%d\n", i);
        } while (result);
    }
    Node* current;
    for (i = 0; i < TABLE_SIZE; i++) {
        current = hash_table->values[i];
        while (current) {
            printf("%s - ", hash_table->values[i]->latin);
            for (j = 0; j < hash_table->values[i]->size; j++) {
                printf("%s\n", hash_table->values[i]->english[j]);
            }
            current = current->next;
        }
    }
    Table_clear(hash_table);
    free(hash_table->values);
    free(hash_table);
    return 0;
}
