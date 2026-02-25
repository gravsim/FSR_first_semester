#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 1000


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


int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
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


void change_weight(
    int N,
    int M,
    int* distances,
    int* visited,
    int* previous,
    int weight,
    int target_x,
    int target_y,
    int parent_x,
    int parent_y) {
    int index = target_y * M + target_x;
    if (target_x >= 0 && target_x < M && target_y >= 0 && target_y < N && !visited[index] && distances[index] > weight) {
        distances[index] = weight;
        previous[index] = parent_y * M + parent_x;
    }
}


int Prim(int N, int M, int V, int** connections, int* distances, int* visited, int* previous) {
    if (!connections) {
        return -1;
    }
    int visited_amount;
    int v;
    int x;
    int y;
    int weight;
    for (visited_amount = 1; visited_amount < V; visited_amount++) {
        v = get_minimal_weight(distances, visited, V);
        if (v == -1) {
            return -1;
        }
        visited[v] = 1;
        x = v % M;
        y = v / M;
        if (x - 1 >= 0) {
            if (connections[y][x - 1] == 2 || connections[y][x - 1] == 3) {
                weight = 0;
            } else {
                weight = 2;
            }
            change_weight(N, M, distances, visited, previous, weight, x-1, y, x, y);
        }
        if (y - 1 >= 0) {
            if (connections[y - 1][x] == 1 || connections[y - 1][x] == 3) {
                weight = 0;
            } else {
                weight = 1;
            }
            change_weight(N, M, distances, visited, previous, weight, x, y-1, x, y);
        }
        if (connections[y][x] == 2 || connections[y][x] == 3) {
            weight = 0;
        } else {
            weight = 2;
        }
        change_weight(N, M, distances, visited, previous, weight, x+1, y, x, y);
        if (connections[y][x] == 1 || connections[y][x] == 3) {
            weight = 0;
        } else {
            weight = 1;
        }
        change_weight(N, M, distances, visited, previous, weight, x, y+1, x, y);
    }
    return 1;
}


void quick_sort(int** main_array, int sort_index, int down, int up) {
    if (down >= up) {
        return;
    }
    int pivot = main_array[(up + down) / 2][sort_index];
    int left = down;
    int right = up;
    while (left <= right) {
        while (main_array[left][sort_index] < pivot) {
            left++;
        }
        while (pivot < main_array[right][sort_index]) {
            right--;
        }
        if (left <= right) {
            swap_int_pointers(main_array + left, main_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, sort_index, down, right);
    quick_sort(main_array, sort_index, left, up);
}


int main(void) {
    int M;
    int N;
    int i;
    int j;
    int added_amount = 0;
    scanf("%d %d", &N, &M);
    int V = M * N;
    int** connections = calloc(N, sizeof(int*));
    for (i = 0; i < N; i++) {
        connections[i] = calloc(M, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", connections[i] + j);
        }
    }
    int* previous = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[0] = 0;
    int sum = 0;
    int* visited = calloc(V, sizeof(int));
    int target_x;
    int target_y;
    Prim(N, M, V, connections, distances, visited, previous);
    for (i = 0; i < V; i++) {
        if (previous[i] != -1) {
            sum += distances[i];
            if (distances[i] > 0) {
                added_amount++;
            }
        }
    }
    int parent_x;
    int parent_y;
    int parent;
    printf("%d %d\n", added_amount, sum);
    int top;
    int left;
    for (i = 0; i < V; i++) {
        if (previous[i] != -1 && distances[i] > 0) {
            target_x = i % M;
            target_y = i / M;
            parent = previous[i];
            parent_x = parent % M;
            parent_y = parent / M;
            if (target_x == parent_x) {
                top = min(target_y, parent_y);
                printf("%d %d 1\n", top+1, target_x+1);
            } else {
                left = min(target_x, parent_x);
                printf("%d %d 2\n", target_y+1, left+1);
            }
        }
    }
    free(distances);
    free(visited);
    free(previous);
    for (i = 0; i < N; i++) {
        free(connections[i]);
    }
    free(connections);
    return 0;
}
