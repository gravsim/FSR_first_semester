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


Queue* init_queue(int N) {
    Queue* queue = malloc(sizeof(Queue));
    queue->front = 0;
    queue->back = 0;
    queue->capacity = N + 1;
    queue->values = (int*)calloc(queue->capacity, sizeof(int));
    return queue;
}


int array_max(int* array, int size) {
    int i;
    int max = 0;
    for (i = 0; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}


int contains(int* array, int size, int element) {
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] == element) {
            return 1;
        }
    }
    return 0;
}


int main(void) {
    int value;
    int N;
    int Q;
    scanf("%i", &N);
    int i;
    Queue* queue = init_queue(N);
    for (i = 0; i < N; i++) {
        scanf("%i", &value);
        push(queue, &value);
    }
    scanf("%i", &Q);
    int* rhymes = calloc(Q, sizeof(int));
    for (i = 0; i < Q; i++) {
        scanf("%i", &rhymes[i]);
    }
    int command1;
    int command2;
    int winner;
    int loser;
    int last_game = array_max(rhymes, Q);
    pop(queue, &command1);
    for (i = 1; i <= last_game; i++) {
        pop(queue, &command2);
        if (contains(rhymes, Q, i)) {
            printf("%i %i\n", command1, command2);
        }
        if (command1 > command2) {
            winner = command1;
            loser = command2;
        } else {
            winner = command2;
            loser = command1;
        }
        push(queue, &loser);
        command1 = winner;
    }
    free(queue->values);
    free(queue);
    free(rhymes);
}
