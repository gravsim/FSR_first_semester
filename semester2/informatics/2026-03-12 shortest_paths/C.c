#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Edge {
    int to;
    int to_time;
    int from_time;
    struct Edge* next;
} Edge;


Edge** set_adjacency_list(int V, int M) {
    int i;
    int j;
    Edge** adjacency_list = calloc(V, sizeof(Edge*));
    int from;
    int to;
    int K;
    int from_time;
    int to_time;
    for (i = 0; i < M; i++) {
        scanf("%d", &K);
        scanf("%d %d", &from, &from_time);
        from--;
        for (j = 0; j < K - 1; j++) {
            scanf("%d %d", &to, &to_time);
            to--;
            Edge* edge1 = malloc(sizeof(Edge));
            edge1->from_time = from_time;
            edge1->to_time = to_time;
            edge1->next = adjacency_list[from];
            adjacency_list[from] = edge1;
            edge1->to = to;
            from = to;
            from_time = to_time;
        }
    }
    return adjacency_list;
}


void free_list(Edge** head) {
    Edge* current = *head;
    Edge* next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}


int free_adjacency_list(Edge** adjacency_list, int V) {
    if (!adjacency_list) {
        return -1;
    }
    int i;
    for (i = 0; i < V; i++) {
        free_list(adjacency_list + i);
    }
    free(adjacency_list);
    return 1;
}


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
    (*heap)->capacity = 1000;
    (*heap)->values = (Node*)calloc((*heap)->capacity, sizeof(Node));
    return 0;
}


int Dijkstra_algorithm(Heap* heap, int** adjacency_matrix, int V, int* distances, int* visited, int* previous) {
    if (!adjacency_matrix || !visited || !distances || !previous) {
        return -1;
    }
    int v;
    int w;
    int value;
    while (heap->size > 0) {
        pop_minimum(heap, &v, &value);
        if (v == -1) {
            return -1;
        }
        if (!visited[v]) {
            visited[v] = 1;
            for (w = 0; w < V; w++) {
                if (adjacency_matrix[v][w] != 1
                && !visited[w]
                && distances[v] + adjacency_matrix[v][w] < distances[w]) {
                    distances[w] = distances[v] + adjacency_matrix[v][w];
                    previous[w] = v;
                    push(heap, w, distances[v] + adjacency_matrix[v][w]);
                }
            }
        }
    }
    return 1;
}


int main(void) {
    int K;
    int N;
    int M;
    int to;
    int from;
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
                from = i * N + j;
            } else if (connections[i][j] == 3) {
                to = i * N + j;
            }
        }
    }
    int* previous = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        distances[i] = INT_MAX;
    }
    distances[from] = 0;
    int* visited = calloc(N, sizeof(int));
    Heap* heap;
    init_heap(&heap);
    push(heap, 0, 0);
    Dijkstra_algorithm(heap, connections, V, distances, visited, previous);
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
