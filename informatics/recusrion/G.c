#include <stdio.h>
#include <stdlib.h>


typedef struct Child {
    long family_size;
    struct Child** children;
} Child;


int kill_family(Child* child, long* deleted) {
    if (!child) {
        return 0;
    }
    long i;
    (*deleted)++;
    for (i = 0; i < child->family_size; i++) {
        kill_family(child->children[i], deleted);
    }
    return 0;
}


int main(void) {
    long N;
    long i;
    long number;
    long pointer;
    long k;
    long deleted = 0;
    scanf("%li", &N);
    Child** numbers = (Child**)calloc(N + 1, sizeof(Child*));
    for (i = 1; i <= N; i++) {
        numbers[i] = (Child*)malloc(sizeof(Child));
        numbers[i]->children = (Child**)calloc(N + 1, sizeof(Child*));
        numbers[i]->family_size = 0;
    }
    for (i = 1; i <= N; i++) {
        scanf("%li %li", &number, &pointer);
        if (pointer > 0) {
            numbers[pointer]->children[numbers[pointer]->family_size++] = numbers[number];
        }
    }
    scanf("%li", &k);
    kill_family(numbers[k], &deleted);
    printf("%li", deleted);
    for (i = 1; i <= N; i++) {
        if (numbers[i]) {
            free(numbers[i]->children);
            free(numbers[i]);
        }
    }
    free(numbers);
    return 0;
}
