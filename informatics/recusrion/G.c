#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    struct Node* next;
} Node;


int main(void) {
    long N;
    long i;
    long number;
    long pointer;
    long k;
    long deleted = 0;
    scanf("%li", &N);
    Node** numbers = (Node**)calloc(N + 1, sizeof(Node*));
    long* previous = (long*)calloc(N + 1, sizeof(long));
    for (i = 0; i < N; i++) {
        scanf("%li %li", &number, &pointer);
        numbers[number] = (Node*)malloc(sizeof(Node));
        numbers[number]->next = NULL;
        previous[number] = pointer;
    }
    for (i = 1; i <= N; i++) {
        if (previous[i] != 0) {
            numbers[previous[i]]->next = numbers[i];
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
    free(numbers);
    free(previous);
    return 0;
}
