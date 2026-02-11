#include <stdio.h>
#include <stdlib.h>


typedef struct Stack {
    int size;
    int max_size;
    char* values;
} Stack;


int expand(Stack* stack) {
    if (!stack) {
        return -1;
    }
    stack->max_size *= 2;
    stack->values = (char*)realloc(stack->values, stack->max_size * sizeof(char));
    return 0;
}


int push(Stack* stack, char value) {
    if (!stack) {
        return -1;
    }
    if (stack->size >= stack->max_size) {
        expand(stack);
    }
    stack->values[stack->size++] = value;
    return 0;
}


char pop(Stack* stack) {
    if (!stack) {
        return -1;
    }
    return stack->values[--stack->size];
}


int is_empty(Stack* stack) {
    return !stack->size;
}


Stack* init_stack(void) {
    Stack* stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->max_size = 256;
    stack->values = (char*)calloc(stack->max_size, sizeof(char));
    return stack;
}


int bracket_equal(char bracket1, char bracket2) {
    return (bracket1 == '(' && bracket2 == ')') ||
    (bracket1 == '[' && bracket2 == ']') ||
    (bracket1 == '{' && bracket2 == '}');
}


int main(void) {
    Stack* stack = init_stack();
    char sequence[256];
    scanf("%s", sequence);
    int i = 0;
    int answer = 1;
    while (answer && sequence[i] != '\0') {
        if (sequence[i] == '(' || sequence[i] == '{' || sequence[i] == '[') {
            push(stack, sequence[i]);
        } else if (is_empty(stack) || !bracket_equal(pop(stack), sequence[i])) {
            answer = 0;
        }
        i++;
    }
    if (!is_empty(stack)) {
        answer = 0;
    }
    if (answer) {
        printf("yes");
    } else {
        printf("no");
    }
    free(stack->values);
    free(stack);
    return 0;
}
