#include <stdio.h>
#include <stdlib.h>


typedef struct Child {
    long id;
    long family_size;
    struct Child** children;
} Child;


int remove_children(Child* child, long* deleted) {
    if (!child) {
        return 0;
    }
    long i;
    (*deleted)++;
    for (i = 0; i < child->family_size; i++) {
        remove_children(child->children[i], deleted);
    }
    return 0;
}


int main(void) {
    long N;
    long i, j;
    long number;
    long pointer;
    long k;
    long deleted = 0;
    scanf("%li", &N);
    Child** numbers = (Child**)calloc(N + 1, sizeof(Child*));
    long* dad_ids = (long*)calloc(N + 1, sizeof(long));
    for (i = 1; i <= N; i++) {
        scanf("%li %li", &number, &pointer);
        numbers[i] = (Child*)malloc(sizeof(Child));
        numbers[i]->children = (Child**)calloc(N + 1, sizeof(Child*));
        numbers[i]->family_size = 0;
        numbers[i]->id = number;
        dad_ids[i] = pointer;
    }
    for (i = 1; i <= N; i++) {
        if (dad_ids[i] > 0) {
            for (j = 1; j <= N; j++) {
                if (dad_ids[i] == numbers[j]->id) {
                    numbers[j]->children[numbers[j]->family_size++] = numbers[i];
                }
            }
        }
    }
    scanf("%li", &k);
    Child* target = NULL;
    i = 1;
    while (i <= N && !target) {
        if (numbers[i]->id == k) {
            target = numbers[i];
        }
        i++;
    }
    remove_children(target, &deleted);
    printf("%li", deleted);
    for (i = 1; i <= N; i++) {
        if (numbers[i]) {
            free(numbers[i]->children);
            free(numbers[i]);
        }
    }
    free(numbers);
    free(dad_ids);
    return 0;
}
