#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define HEAP_CAPACITY 1000

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
    (*heap)->capacity = HEAP_CAPACITY;
    (*heap)->values = (Node*)calloc((*heap)->capacity, sizeof(Node));
    return 0;
}


int check_vertex(Heap* heap,
    int N,
    int M,
    int** connections,
    int* distances,
    int* visited,
    int x,
    int y,
    int parent_x,
    int parent_y) {
    int index = y * M + x;
    int parent_index = parent_y * M + parent_x;
    if (x >= 0
        && x < M
        && y >= 0
        && y < N
        && connections[y][x] != 1
        && !visited[index]
        && distances[index] > distances[parent_index] + 1) {
        distances[index] = distances[parent_index] + 1;
        push(heap, index, distances[index]);
    }
    return 1;
}


int Dijkstra_algorithm(int N, int M, Heap* heap, int** connections, int V, int* distances, int* visited, int* previous) {
    if (!connections || !visited || !distances || !previous) {
        return -1;
    }
    int v;
    int value;
    int x;
    int y;
    while (heap->size > 0) {
        pop_minimum(heap, &v, &value);
        if (v == -1) {
            return -1;
        }
        if (!visited[v]) {
            visited[v] = 1;
            x = v % M;
            y = v / M;
            check_vertex(heap, N, M, connections, distances, visited, x+1, y, x, y);
            check_vertex(heap, N, M, connections, distances, visited, x-1, y, x, y);
            check_vertex(heap, N, M, connections, distances, visited, x, y+1, x, y);
            check_vertex(heap, N, M, connections, distances, visited, x, y-1, x, y);
        }
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
    int* previous = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = INT_MAX;
    }
    distances[from] = 0;
    int* visited = calloc(V, sizeof(int));
    Heap* heap;
    init_heap(&heap);
    push(heap, from, 0);
    Dijkstra_algorithm(N, M, heap, connections, V, distances, visited, previous);
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
