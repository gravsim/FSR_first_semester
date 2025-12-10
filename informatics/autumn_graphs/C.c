#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int N;
    scanf("%d", &N);
    char** connections = calloc(N - 1, sizeof(char*));
    int i;
    int j;
    int answer = 1;
    for (i = 0; i < N - 1; i++) {
        connections[i] = calloc(N - 1, sizeof(char));
    }
    for (i = 0; i < N - 1; i++) {
        scanf("%s", connections[i]);
    }
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - 1 - i; j++) {
            if (connections[i][j] != 1) {
                answer = 0;
            }
        }
    }
    if (answer) {
        printf("YES");
    } else {
        printf("NO");
    }
    for (i = 0; i < n; i++) {
        free(connections[i]);
    }
    free(connections);
    return 0;
}
