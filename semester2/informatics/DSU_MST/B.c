#include <stdio.h>
#include <stdlib.h>


int** set_adjacency_matrix(int n) {
    int i;
    int** adjacency_matrix = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        adjacency_matrix[i] = calloc(n, sizeof(int));
    }
    return adjacency_matrix;
}


int BFS(int** adjacency_matrix, int n, int source) {
    if (!adjacency_matrix) {
        return -1;
    }
    int* visited = calloc(n, sizeof(int));
    int* queue = calloc(n, sizeof(int));
    int front = 0;
    int back = 0;
    int weight = 0;
    int current;
    int i;
    visited[source] = 1;
    queue[back++] = source;
    while (front < back) {
        current = queue[front];
        for (i = 0; i < n; i++) {
            if (adjacency_matrix[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[back++] = i;
                weight += adjacency_matrix[current][i];
            }
        }
        front++;
    }
    free(visited);
    free(queue);
    return weight;
}


int main(void) {
    int n;
    int m;
    int i;
    int command;
    int x;
    int y;
    int w;
    scanf("%d %d", &n, &m);
    int** adjacency_matrix = set_adjacency_matrix(n);
    for (i = 0; i < m; i++) {
        scanf("%d ", &command);
        switch (command) {
            case 1:
                scanf("%d %d %d", &x, &y, &w);
                x--;
                y--;
                adjacency_matrix[x][y] += w;
                break;
            case 2:
                scanf("%d", &x);
                x--;
                printf("\n%d", BFS(adjacency_matrix, n, x));
                break;
            default: ;
        }
    }
    for (i = 0; i < n; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return 0;
}
