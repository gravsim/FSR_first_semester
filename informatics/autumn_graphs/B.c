#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    if (m != n * (n - 1) / 2) {
        printf("NO");
        return 0;
    }
    int** connections = calloc(n, sizeof(int*));
    int i;
    int j;
    int x;
    int y;
    int answer = 1;
    for (i = 0; i < n; i++) {
        connections[i] = calloc(n, sizeof(int));
    }
    for (i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        connections[x - 1][y - 1]++;
        connections[y - 1][x - 1]++;
    }
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
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
