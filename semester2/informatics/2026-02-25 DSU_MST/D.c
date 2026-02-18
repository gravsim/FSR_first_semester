#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WEIGHT 100


int swap_int_pointers(int** a, int** b) {
    if (!a || !b) {
        return -1;
    }
    int* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}

int swap_int(int* a, int* b) {
    if (!a || !b) {
        return -1;
    }
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int get_minimal_weight(int* distances, int* visited, int V) {
    if (!distances || !visited) {
        return -1;
    }
    int i = 0;
    int minimum = MAX_WEIGHT;
    int min_index = -1;
    for (i = 0; i < V; i++) {
        if (!visited[i] && distances[i] < minimum) {
            minimum = distances[i];
            min_index = i;
        }
    }
    return min_index;
}


int** set_adjacency_matrix(int V, int M, int** edges) {
    int i;
    int vertex1;
    int vertex2;
    int weight;
    int** adjacency_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(V, sizeof(int));
    }
    for (i = 0; i < M; i++) {
        vertex1 = edges[i][0];
        vertex2 = edges[i][1];
        weight = edges[i][2];

        adjacency_matrix[vertex1][vertex2] = weight;
        adjacency_matrix[vertex2][vertex1] = weight;
    }
    return adjacency_matrix;
}


int free_adjacency_matrix(int** adjacency_matrix, int V) {
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    for (i = 0; i < V; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return 1;
}


int Prim(int V, int** adjacency_matrix, int* previous) {
    /*
        In this program array `previous` is not used. I will keep it
        if in future I will need to construct gotten tree.
    */
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    int w;
    int visited_amount;
    int answer = 0;
    int v;
    for (i = 0; i < V; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[0] = 0;
    int* visited = calloc(V, sizeof(int));
    for (visited_amount = 1; visited_amount < V; visited_amount++) {
        v = get_minimal_weight(distances, visited, V);
        visited[v] = 1;
        for (w = 0; w < V; w++) {
            if (adjacency_matrix[v][w]
            && !visited[w]
            && adjacency_matrix[v][w] < distances[w]) {
                previous[w] = v;
                distances[w] = adjacency_matrix[v][w];
            }
        }
    }
    for (i = 0; i < V; i++) {
        answer += distances[i];
    }
    free(distances);
    free(visited);
    return answer;
}


void quick_sort(int** main_array, int size, int down, int up) {
    if (down >= up) {
        return;
    }
    int pivot = main_array[(up + down) / 2][1];
    int left = down;
    int right = up;
    while (left <= right) {
        while (main_array[left][1] < pivot) {
            left++;
        }
        while (pivot < main_array[right][1]) {
            right--;
        }
        if (left <= right) {
            swap_int_pointers(main_array + left, main_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, size, down, right);
    quick_sort(main_array, size, left, up);
}



int main(void) {
    int V;
    int E;
    int i;
    int j;
    scanf("%d %d", &V, &E);
    if (E < V - 1) {
        printf("Impossible");
        return 0;
    }
    int* previous = calloc(V, sizeof(int));
    int** edges = calloc(E, sizeof(int*));
    for (i = 0; i < E; i++) {
        edges[i] = calloc(3, sizeof(int));
        scanf("%d %d %d", edges[i], edges[i] + 1, edges[i] + 2);
        edges[i][0]--;
        edges[i][1]--;
    }
    int** adjacency_matrix = set_adjacency_matrix(V, E, edges);
    int max_price;
    int min_price;
    int max_length;
    int min_length;
    scanf("%d %d %d %d", &max_price, &max_length, &min_price, &min_length);
    int is_swapped = 0;
    if (max_price < min_price) {
        swap_int(&max_price, &min_price);
        swap_int(&max_length, &min_length);
        is_swapped = 1;
    }
    int** final_edges = calloc(E, sizeof(int*));
    for (i = 0; i < E; i++) {
        final_edges[i] = calloc(2, sizeof(int));
    }
    printf("%d", Prim(V, adjacency_matrix, previous));
    int edges_amount = 0;
    for (i = 0; i < V - 1; i++) {
        for (j = 0; j < V - 1; j++) {
            if (edges[i][0] == previous[j] && edges[i][1] == j) {
                final_edges[edges_amount][0] = i;
                final_edges[edges_amount][1] = edges[i][2];
                edges_amount++;
            }
        }
    }
    quick_sort(final_edges, edges_amount, 0, edges_amount - 1);
    free_adjacency_matrix(adjacency_matrix, V);
    return 0;
}
