#include <stdio.h>
#include <stdlib.h>


#define CHUNK_SIZE (8 * sizeof(unsigned long long))


unsigned long long** allocate_matrix(int size, int numbers) {
    unsigned long long** matrix = calloc(size, sizeof(unsigned long long*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = calloc(numbers, sizeof(unsigned long long));
    }
    return matrix;
}


unsigned long long check_bit(unsigned long long number, int bit_index) {
    if (number & 1ULL << (bit_index % CHUNK_SIZE)) {
        return 1;
    }
    return 0;
}


void set_bit(unsigned long long* number, int bit_index) {
    *number |= 1ULL << (bit_index % CHUNK_SIZE);
}


int DFS_recursive(unsigned long long** connections,
                    int* colors,
                    int current,
                    int N) {
    if (!connections || !colors) {
        return -1;
    }
    colors[current] = 1;
    int i;
    for (i = 0; i < N; i++) {
        if (check_bit(connections[current][i / CHUNK_SIZE], i)
            && check_bit(connections[current][i / CHUNK_SIZE], i) != check_bit(connections[i][current / CHUNK_SIZE], current)) {
            // Второе условие проверяет, что нет прохода по одному
            // и тому же ребру, чтобы цикл был простой
            if (colors[i] == 1 ||
                (colors[i] == 0 && DFS_recursive(connections, colors, i, N))) {
                return 1;
            }
        }
    }
    colors[current] = 2;
    return 0;
}


int check_cycles(unsigned long long** connections, int V) {
    int i;
    int* colors = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        if (colors[i] == 0
            && DFS_recursive(connections, colors, i, V)) {
            return 1;
        }
    }
    free(colors);
    return 0;
}


int main(void) {
    /*
     Сложность в том, что нужно определить, есть ли простой цикл, а
     значит он не может проходит по одному и тому же ребру дважды.
    */
    int V;
    int E;
    scanf("%d %d", &V, &E);
    int numbers = (V + CHUNK_SIZE - 1) / CHUNK_SIZE;
    int i;
    int j;
    unsigned long long** connections = allocate_matrix(V, numbers);
    int* borders = calloc(V + 1, sizeof(int));
    int* vertices = calloc(E, sizeof(int));
    int* weights = calloc(E, sizeof(int));
    // Массив weights бесполезен
    for (i = 0; i < V + 1; i++) {
        scanf("%d", &borders[i]);
    }
    for (i = 0; i < E; i++) {
        scanf("%d", &vertices[i]);
    }
    for (i = 0; i < E; i++) {
        scanf("%d", &weights[i]);
    }
    for (i = 0; i < V; i++) {
        for (j = borders[i]; j < borders[i + 1]; j++) {
            set_bit(&connections[i][vertices[j] / CHUNK_SIZE], vertices[j]);
        }
    }
    if (check_cycles(connections, V)) {
        printf("YES");
    } else {
        printf("NO");
    }
    for (i = 0; i < V; i++) {
        free(connections[i]);
    }
    free(connections);
    free(borders);
    free(vertices);
    free(weights);
    return 0;
}
