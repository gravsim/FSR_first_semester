#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    struct Node* next;
} Node;


int main(void) {
    long N;
    long i;
    long number;
    long previous;
    long k;
    long deleted = 0;
    scanf("%li", &N);
    Node** numbers = (Node**)calloc(N, sizeof(Node*));
    for (i = 0; i < N; i++) {
        scanf("%li %li", &number, &previous);
        numbers[number] = (Node*)malloc(sizeof(Node));
        numbers[number]->next = NULL;
        if (previous != 0) {
            numbers[previous]->next = numbers[number];
        }
    }
    scanf("%li", &k);
    Node* current = numbers[k];
    while (current) {
        deleted++;
        current = current->next;
    }
    printf("%li", deleted);
    for (i = 0; i < N; i++) {
        free(numbers[i]);
    }
    return 0;
}
