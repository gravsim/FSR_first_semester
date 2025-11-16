#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int value;
    struct Node* next;
    struct Node* previous;
} Node;


int insert(Node** beg_pp, Node** end_pp, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return -2;
    }
    new_node->value = value;
    new_node->next = NULL;
    new_node->previous = *end_pp;
    *end_pp = new_node;
    if (!*beg_pp) {
        *beg_pp = new_node;
        return 0;
    }
    Node* tail = *beg_pp;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = new_node;
    return 0;
}


int print_list(Node* beg_p) {
    if (!beg_p) {
        printf("Empty list\n");
        return 1;
    }
    Node* current = beg_p;
    while (current) {
        printf("%d", current->value);
        current = current->next;
        if (current) {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}


int search_element(Node** beg_pp, int target, Node** result) {
    Node* current = *beg_pp;
    while (current) {
        if (current->value == target) {
            *result = current;
            return 0;
        }
        current = current->next;
    }
    return 1;
}



int read_list(int list_len, Node** beg_pp, Node** end_pp) {
    int i;
    int number;
    for (i = 0; i < list_len; i++) {
        scanf("%d", &number);
        insert(beg_pp, end_pp, number);
    }
    return 0;
}


int main(void) {
    int len;
    int target;
    Node* result;
    scanf("%d ", &len);
    Node* beg_p = NULL;
    Node* end_p = NULL;
    Node* next;
    Node* current = beg_p;
    read_list(len, &beg_p, &end_p);
    do {
        scanf("%d", &target);
    } while (search_element(&beg_p, target, &result));
    print_list(beg_p);
    while (current) {
        next = current->next;
        free(current);
        current = next; 
    }
    return 0;
}
