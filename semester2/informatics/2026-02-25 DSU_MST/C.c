#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int** set_adjacency_matrix(int N) {
    int i;
    int** adjacency_matrix = calloc(N, sizeof(int*));
    for (i = 0; i < N; i++) {
        adjacency_matrix[i] = calloc(N, sizeof(int));
    }
    return adjacency_matrix;
}


typedef struct DSU_node {
    struct DSU_node* parent;
    int sum;
    int rang;
} DSU_node;


DSU_node* make_set(int sum) {
    DSU_node* tmp = malloc(sizeof(DSU_node));
    tmp->sum = sum;
    tmp->parent = tmp;
    tmp->rang = 1;
    return tmp;
}


DSU_node* find_set(DSU_node* node) {
    if (node->parent == node) {
        return node;
    }
    return node->parent = find_set(node->parent);
}


DSU_node* union_set(DSU_node* node1, DSU_node* node2) {
    if (!node1 || !node2) {
        return NULL;
    }
    node1 = find_set(node1);
    node2 = find_set(node2);
    if (node1 == node2) {
        return node1;
    }
    if (node1->rang < node2->rang) {
        DSU_node* tmp = node1;
        node1 = node2;
        node2 = tmp;
    }
    node2->parent = node1;
    if (node1->rang == node2->rang) {
        node1->rang++;
    }
    node1->sum += node2->sum;
    return node1;
}


typedef struct Heap {
    int size;
    int capacity;
    double* values;
} Heap;


int swap(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


int expand(Heap* heap) {
    if (!heap) {
        return -1;
    }
    heap->capacity *= 2;
    heap->values = (double*)realloc(heap->values, heap->capacity * sizeof(double));
    return 1;
}


int sift_up(Heap* heap, int index) {
    if (!heap) {
        return -1;
    }
    while (index > 0 && heap->values[index] < heap->values[(index - 1) / 2]) {
        swap(&heap->values[index], &heap->values[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
    return 1;
}


int sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2] < heap->values[max_index]) {
        max_index = 2 * index + 2;
    }
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1] <= heap->values[max_index]) {
        max_index = 2 * index + 1;
    }
    /*
        Тут знак >=, т.к. при равенстве элементов по условию задачи,
        нужно выбирать левого сына, который имеет индекс 2 * index + 1.
    */
    if (max_index != index) {
        swap(&heap->values[index], &heap->values[max_index]);
        return sift_down(heap, max_index);
    }
    return max_index;
}


int push(Heap* heap, int value) {
    if (!heap) {
        return -1;
    }
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size] = value;
    sift_up(heap, heap->size);
    heap->size++;
    return 1;
}


int print_heap(Heap* heap) {
    if (!heap) {
        return -1;
    }
    int i;
    for (i = 0; i < heap->size; i++) {
        printf("%lf ", heap->values[i]);
    }
    return 1;
}


int decrease(Heap* heap, int index, int value) {
    heap->values[index] -= value;
    return sift_down(heap, index) + 1;
}


int init_heap(Heap** heap) {
    if (!heap) {
        return -1;
    }
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 5;
    (*heap)->values = (double*)calloc((*heap)->capacity, sizeof(double));
    return 1;
}


int forms_cycle(int* edges, int new_adge) {


}


int flatten_indices(int N, int i, int j) {
    return i * (N - 1) - i * (i + 1) / 2 + j;
}


int Kruskal(Heap* heap, int N, DSU_node** nodes) {
    int edges_amount = 0;
    int i;
    int x;
    int y;
    while (edges_amount < N - 1) {
        if (find_set(nodes[x]) != find_set(nodes[y])) {
            union_set(nodes[x], nodes[y]);
            edges_amount++;
        }

    }
    return find_set(nodes[edges_amount])->sum;
}


int main(void) {
    int N;
    int M;
    int i;
    int j;
    scanf("%d", &N);
    Heap* heap;
    init_heap(&heap);
    int** adjacency_matrix = set_adjacency_matrix(N);
    int** positions = calloc(N, sizeof(int*));
    DSU_node** nodes = calloc(N, sizeof(DSU_node*));
    double* edges = calloc(N * (N - 1) / 2, sizeof(int));
    for (i = 0; i < N; i++) {
        positions[i] = calloc(2, sizeof(int));
        nodes[i] = make_set(0);
    }
    for (i = 0; i < N; i++) {
        scanf("%d %d", positions[i], positions[i] + 1);
    }
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            push(heap, sqrt(positions[i][0] ^ 2 - positions[j][1] ^ 2));
        }
    }
    printf("%d", Kruskal(edges, N, nodes));
    scanf("%d", &M);
    for (i = 0; i < M; i++) {
        scanf("%d %d", positions[i], positions[i] + 1);
    }


    return 0;
}
