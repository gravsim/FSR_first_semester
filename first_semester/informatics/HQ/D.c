#include <stdio.h>
#include <stdlib.h>


typedef struct Heap {
    int size;
    int capacity;
    int* values;
} Heap;


int swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


int is_empty(Heap* heap) {
    return heap->size == 0;
}


void expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (int*)realloc(heap->values, heap->capacity * sizeof(int));
}


int sift_up(Heap* heap, int index) {
    while (index > 0 && heap->values[index] < heap->values[(index - 1) / 2]) {
        swap(&heap->values[index], &heap->values[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
    return 0;
}


int sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1] < heap->values[index]) {
        max_index = 2 * index + 1;
    }
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2] < heap->values[max_index]) {
        max_index = 2 * index + 2;
    }
    if (max_index != index) {
        swap(&heap->values[index], &heap->values[max_index]);
        sift_down(heap, max_index);
    }
    return 0;
}


int push(Heap* heap, int value) {
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size] = value;
    sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int pop_minimum(Heap* heap, int* value) {
    *value = heap->values[0];
    heap->values[0] = heap->values[--heap->size];
    sift_down(heap, 0);
    return 0;
}


int clear(Heap* heap) {
    if (!heap) {
        return -1;
    }
    heap->size = 0;
    return 1;
}


int check_heap(Heap* heap) {
    int true_false = is_empty(heap);
    if (true_false) {
        printf("CANNOT\n");
    }
    return !true_false;
}


int init_heap(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 5;
    (*heap)->values = (int*)calloc((*heap)->capacity, sizeof(int));
    return 0;
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
    /*
        В этой задаче используем кучу с минимумом в корне.
    */
    int value;
    Heap* heap;
    init_heap(&heap);
    char command[20];
    while (scanf("%15s", command) == 1) {
        if (is_str_equal("ADD", command)) {
            scanf(" %d", &value);
            push(heap, value);
        } else if (is_str_equal("EXTRACT", command)) {
            if (check_heap(heap)) {
                pop_minimum(heap, &value);
                printf("%d\n", value);
            }
        } else if (is_str_equal("CLEAR", command)) {
            clear(heap);
        }
    }
    free(heap->values);
    free(heap);
    return 0;
}
