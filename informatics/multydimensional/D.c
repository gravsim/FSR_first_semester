#include <stdio.h>


void check(int x, int y, int N, int M, int array[20][20]) {
    if (x > 0 && x <= N && y > 0 && y <= M && array[x - 1][y - 1] < 9) {
        array[x - 1][y - 1]++;
    }
}


int main() {
    int N;
    int M;
    int array[5000][5000];
    scanf("%d %d %d", &N, &M);
    int i, j;
    int x, y;
    int number;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &number);
            array[i][j] = number;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (array[i][j] == 0) {
                printf(". ");
            } else if (array[i][j] == 9) {
                printf("* ");
            } else {
                printf("%d ", array[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}
