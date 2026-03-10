#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define HEAP_CAPACITY 1000


typedef struct Node {
    int index;
    int weight;
} Node;


typedef struct Heap {
    int size;
    int capacity;
    Node* values;
} Heap;


int swap_nodes(Node* a, Node* b) {
    Node tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


void expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (Node*)realloc(heap->values, heap->capacity * sizeof(Node));
}


int sift_up(Heap* heap, int index) {
    while (index > 0 && heap->values[index].weight < heap->values[(index - 1) / 2].weight) {
        swap_nodes(heap->values + index, heap->values + (index - 1) / 2);
        index = (index - 1) / 2;
    }
    return 0;
}


int sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2].weight < heap->values[max_index].weight) {
        max_index = 2 * index + 2;
    }
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1].weight < heap->values[max_index].weight) {
        max_index = 2 * index + 1;
    }
    if (max_index != index) {
        swap_nodes(&heap->values[index], &heap->values[max_index]);
        return sift_down(heap, max_index);
    }
    return max_index;
}


int push(Heap* heap, int index, int value) {
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size].weight = value;
    heap->values[heap->size].index = index;
    sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int pop_minimum(Heap* heap, int* index, int* value) {
    *value = heap->values[0].weight;
    *index = heap->values[0].index;
    heap->values[0] = heap->values[--heap->size];
    return sift_down(heap, 0) + 1;
}


int init_heap(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = HEAP_CAPACITY;
    (*heap)->values = (Node*)calloc((*heap)->capacity, sizeof(Node));
    return 0;
}


int is_right_turn(int* vector1, int* vector2) {
    return vector1[0] * vector2[1] - vector2[0] * vector1[1] < 0;
}


int check_vertex(Heap* heap,
    int K,
    int N,
    int M,
    int* direction,
    int** connections,
    int* distances,
    int** directions,
    int* right_turns,
    int* visited,
    int parent_x,
    int parent_y) {

    int y = parent_y + direction[0];
    int x = parent_x + direction[1];
    int index = y * M + x;
    int parent_index = parent_y * M + parent_x;

    if (x >= 0
        && x < M
        && y >= 0
        && y < N
        && connections[y][x] != 1
        && distances[index] > distances[parent_index] + 1) {

        if (is_right_turn(directions[parent_index], direction)) {
            right_turns[index] = right_turns[parent_index] + 1;
            if (right_turns[index] <= K) {
                directions[index][0] = direction[0];
                directions[index][1] = direction[1];
                distances[index] = distances[parent_index] + 1;
                push(heap, index, distances[index]);
            }
        } else {
            right_turns[index] = right_turns[parent_index];
            directions[index][0] = direction[0];
            directions[index][1] = direction[1];
            distances[index] = distances[parent_index] + 1;
            push(heap, index, distances[index]);
        }

    }
    return 1;
}


int Dijkstra_algorithm(
    int K,
    int N,
    int M,
    Heap* heap,
    int** connections,
    int V,
    int* distances,
    int** directions,
    int* right_turns,
    int* visited) {
    if (!connections || !visited || !distances) {
        return -1;
    }
    int v;
    int value;
    int paretn_x;
    int parent_y;
    int up[2] = {-1, 0};
    int down[2] = {1, 0};
    int right[2] = {0, 1};
    int left[2] = {0, -1};

    while (heap->size > 0) {
        pop_minimum(heap, &v, &value);
        if (v == -1) {
            return -1;
        }

            paretn_x = v % M;
            parent_y = v / M;
            check_vertex(heap, K, N, M, up, connections, distances, directions, right_turns, visited, paretn_x, parent_y);
            check_vertex(heap, K, N, M, down, connections, distances, directions, right_turns, visited, paretn_x, parent_y);
            check_vertex(heap, K, N, M, right, connections, distances, directions, right_turns, visited, paretn_x, parent_y);
            check_vertex(heap, K, N, M, left, connections, distances, directions, right_turns, visited, paretn_x, parent_y);

    }
    return 1;
}


int main(void) {
    int K;
    int N;
    int M;
    int to = -1;
    int from = -1;
    int i;
    int j;
    scanf("%d %d %d", &K, &N, &M);
    int V = M * N;
    int** connections = calloc(N, sizeof(int*));
    for (i = 0; i < N; i++) {
        connections[i] = calloc(M, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", connections[i] + j);
            if (connections[i][j] == 2) {
                from = i * M + j;
            } else if (connections[i][j] == 3) {
                to = i * M + j;
            }
        }
    }
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = INT_MAX;
    }
    distances[from] = 0;
    int** directions = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        directions[i] = calloc(2, sizeof(int));
    }
    int* right_turns = calloc(V, sizeof(int));
    int* visited = calloc(V, sizeof(int));
    Heap* heap;
    init_heap(&heap);
    directions[from][0] = 0;
    directions[from][1] = 1;
    push(heap, from, 0);
    Dijkstra_algorithm(K, N, M, heap, connections, V, distances, directions, right_turns, visited);
    if (distances[to] == INT_MAX) {
        printf("-1");
    } else {
        printf("%d", distances[to]);
    }

    free(distances);
    free(heap->values);
    free(heap);
    return 0;
}
