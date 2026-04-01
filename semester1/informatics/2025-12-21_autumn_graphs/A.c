#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int N;
    scanf("%d", &N);
    int** connections = calloc(N, sizeof(int*));
    int* colors = calloc(N, sizeof(int));
    int i;
    int j;
    int answer = 0;
    for (i = 0; i < N; i++) {
        connections[i] = calloc(N, sizeof(int));
        for (j = 0; j < N; j++) {
            scanf("%d", &connections[i][j]);
        }
    }
    for (i = 0; i < N; i++) {
        scanf(" %d", &colors[i]);
    }
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            if (connections[i][j] == 1 && colors[i] != colors[j]) {
                answer++;
            }
        }
    }
    printf("%d", answer);
    for (i = 0; i < N; i++) {
        free(connections[i]);
    }
    free(connections);
    free(colors);
    return 0;
}
