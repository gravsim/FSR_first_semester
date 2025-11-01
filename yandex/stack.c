#include <stdio.h>
#include <stdlib.h>


struct stack {
    int size;
    int max_size;
    char* values;
};


void expand(struct stack* stack) {
    stack->values = (char*)realloc(stack->values, 2 * stack->max_size * sizeof(char));
    stack->max_size *= 2;
}


int push(struct stack* stack, char* element) {
    if (stack->size >= stack->max_size) {
        expand(stack);
    }
    stack->values[stack->size] = *element;
    (stack->size)++;
    return 1;
}


int pop(struct stack* stack, char* element) {
    *element = stack->values[(stack->size) - 1];
    (stack->size)--;
    return 1;
}


int top(struct stack* stack, char* element) {
    *element = stack->values[stack->size - 1];
    return 1;
}


int is_empty(struct stack* stack, int* element) {
    *element = !stack->size;
    return 1;
}


int clear(struct stack* stack) {
    stack->size = 0;
    return 1;
}


int check_stack(struct stack* stack) {
    int true_false;
    is_empty(stack, &true_false);
    if (true_false) {
        printf("Stack is empty\n");
    }
    return !true_false;
}


int main() {
    int command;
    char element;
    struct stack* stack = (struct stack*)malloc(sizeof(struct stack));
    stack->size = 0;
    stack->max_size = 100;
    stack->values = (char*)calloc(stack->max_size, sizeof(char));
    do {
        scanf("%i", &command);
        switch (command) {
            case 1:
                scanf(" %c", &element);
                push(stack, &element);
                break;
            case 2:
                if (check_stack(stack)) {
                    pop(stack, &element);
                }
                break;
            case 3:
                if (check_stack(stack)) {
                    top(stack, &element);
                    printf("%c\n", element);
                }
                break;
            case 4:
                int true_false;
                is_empty(stack, &true_false);
                printf("%i\n", true_false);
                break;
            case 5:
                clear(stack);
                break;
            default:
                break;
        }
    } while (command != 0);
    free(stack->values);
    free(stack);
    return 0;
}
