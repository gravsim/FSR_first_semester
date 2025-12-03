#include <stdio.h>
#include <stdlib.h>


typedef struct Stack {
    int size;
    int max_size;
    int* values;
} Stack;


typedef struct Barge {
    Stack** cargo_boxes;
    int boxes_number;
    int max_boxes;
} Barge;


int expand(Stack* stack) {
    if (!stack) {
        return -1;
    }
    stack->max_size *= 2;
    stack->values = (int*)realloc(stack->values, stack->max_size * sizeof(int));
    return 0;
}


int push(Stack* stack, int value) {
    if (!stack) {
        return -1;
    }
    if (stack->size >= stack->max_size) {
        expand(stack);
    }
    stack->values[stack->size++] = value;
    return 0;
}


int is_empty(Stack* stack) {
    return !stack->size;
}


int pop(Stack* stack) {
    if (!stack) {
        return -1;
    }
    if (is_empty(stack)) {
        return -1;
    }
    return stack->values[--stack->size];
}


Stack* init_stack(void) {
    Stack* stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->max_size = 100;
    stack->values = (int*)calloc(stack->max_size, sizeof(int));
    return stack;
}


Barge* init_barge(int K) {
    int i;
    Barge* barge = malloc(sizeof(Barge));
    barge->max_boxes = 0;
    barge->boxes_number = 0;
    barge->cargo_boxes = calloc(K, sizeof(Stack*));
    for (i = 0; i < K; i++) {
        barge->cargo_boxes[i] = init_stack();
    }
    return barge;
}


int main(void) {
    int N;
    int K;
    int P;
    char action;
    int cargo_index;
    int fuel_type;
    int value;
    int answer = 1;
    int i = 0;
    scanf("%i %i %i", &N, &K, &P);
    Barge* barge = init_barge(K);
    while (answer && i < N) {
        scanf(" %c %i %i", &action, &cargo_index, &fuel_type);
        cargo_index--;
        switch (action) {
            case '+':
                push(barge->cargo_boxes[cargo_index], fuel_type);
                barge->boxes_number++;
                if (barge->boxes_number > barge->max_boxes) {
                    barge->max_boxes = barge->boxes_number;
                }
                if (barge->boxes_number > P) {
                    answer = 0;
                }
                break;
            case '-':
                value = pop(barge->cargo_boxes[cargo_index]);
                if (value == fuel_type) {
                    barge->boxes_number--;
                } else {
                    answer = 0;
                }
                break;
            default:
                break;
        }
        i++;
    }
    if (answer == 0 || barge->boxes_number > 0) {
        printf("Error");
    } else {
        printf("%i", barge->max_boxes);
    }
    for (i = 0; i < K; i++) {
        free(barge->cargo_boxes[i]->values);
        free(barge->cargo_boxes[i]);
    }
    free(barge->cargo_boxes);
    free(barge);
    return 0;
}
