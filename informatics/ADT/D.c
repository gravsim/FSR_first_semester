#include <stdio.h>
#include <stdlib.h>


typedef struct Queue {
    int front;
    int back;
    int capacity;
    int* values;
} Queue;


int norm_index(Queue* queue, int index) {
    return (index % queue->capacity + queue->capacity) % queue->capacity;
}


int is_full(Queue* queue) {
    if (!queue) {
        return 0;
    }
    return queue->back - queue->front == queue->capacity;
}


int is_empty(Queue* queue) {
    if (!queue) {
        return 0;
    }
    return queue->front == queue->back;
}


void expand(Queue* queue) {
    if (!queue) {
        return;
    }
    queue->front = norm_index(queue, queue->front);
    queue->back = norm_index(queue, queue->back);
    int old_capacity = queue->capacity;
    queue->capacity *= 2;
    int* tmp_values = realloc(queue->values, queue->capacity * sizeof(int));
    if (!tmp_values) {
        return;
    }
    queue->values = tmp_values;
    int i;
    if (queue->front >= queue->back) {
        for (i = 0; i < queue->back; i++) {
            queue->values[i + old_capacity] = queue->values[i];
        }
        queue->back += old_capacity;
    }
}


int push(Queue* queue, int* value) {
    if (!queue || !value) {
        return -1;
    }
    if (is_full(queue)) {
        expand(queue);
    }
    queue->values[norm_index(queue, queue->back)] = *value;
    queue->back++;
    return 0;
}


int pop(Queue* queue, int* value) {
    if (!queue || !value) {
        return -1;
    }
    *value = queue->values[norm_index(queue, queue->front)];
    queue->front++;
    return 0;
}


int front(Queue* queue, int* value) {
    if (!queue || !value) {
        return -1;
    }
    *value = queue->values[norm_index(queue, queue->front)];
    return 0;
}


int clear(Queue* queue) {
    if (!queue) {
        return -1;
    }
    queue->front = 0;
    queue->back = 0;
    return 0;
}


int check_queue(Queue* queue) {
    int true_false = is_empty(queue);
    if (true_false) {
        printf("error\n");
    }
    return !true_false;
}


Queue* init_queue(void) {
    Queue* queue = malloc(sizeof(Queue));
    queue->front = 0;
    queue->back = 0;
    queue->capacity = 100;
    queue->values = (int*)calloc(queue->capacity, sizeof(int));
    return queue;
}


int is_str_equal(char* sample, char* command) {
    int i = 0;
    while (command[i] != '\0') {
        if (command[i] != sample[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}


int main(void) {
    int value;
    char command[20];
    Queue* queue = init_queue();
    while (1) {
        scanf("%s", command);
        if (is_str_equal("push", command)) {
            scanf(" %i", &value);
            push(queue, &value);
            printf("ok\n");
        } else if (is_str_equal("pop", command)) {
            if (check_queue(queue)) {
                pop(queue, &value);
                printf("%i\n", value);
            }
        } else if (is_str_equal("front", command)) {
            if (check_queue(queue)) {
                front(queue, &value);
                printf("%i\n", value);
            }
        } else if (is_str_equal("size", command)) {
            printf("%i\n", queue->back - queue->front);
        } else if (is_str_equal("clear", command)) {
            clear(queue);
            printf("ok\n");
        } else if (is_str_equal("exit", command)) {
            free(queue->values);
            free(queue);
            printf("bye\n");
            return 0;
        }
    }
}
