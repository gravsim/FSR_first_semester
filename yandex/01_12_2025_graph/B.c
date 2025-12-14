#include <stdio.h>
#include <stdlib.h>


unsigned long long** allocate_matrix(int size) {
    unsigned long long** matrix = calloc(size, sizeof(unsigned long long*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = calloc(size, sizeof(unsigned long long));
    }
    return matrix;
}


int main(void) {
    /*
     Т.к. булов в си нету, будем хранить значения есть/нету
     пути из вершины i в вершину j
     в битах 64-разрядных чисел. Таких чисел понадобится
     (N + 63) / 64 (округление в большую сторону).
     Создаем два массива с числами, в которых будем хранить
     состояния посещенных вершин: red_reached: N * N, blue_reached: N ^ N.
     В i-й строке j-м столбце матрицы стоит 1, если из i-й вершины
     в j-ю есть путь только по цвету матрицы. Иначе стоит 0 (одноцветного пути нет).
    */
    int N;
    int target;
    scanf("%d %d", &N, &target);
    unsigned long long** connections = allocate_matrix(N);
    char letter;
    int i;
    int j;
    int k;
    int numbers = (N + 63) / 64;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%c", &letter);
            connections[i][j / 64] |= 1ULL << (j % 64);
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (connections[i][j]) {
                for (k = 0; k < numbers; k++) {
                    connections[i][k] |= connections[j][k];
                }
            }
        }
    }
    for (i = 0; i < N; i++) {
        if (connections[target][i / 64] & 1ULL << (i % 64)) {
            printf("%d ", i);
        }
    }
    for (i = 0; i < N; i++) {
        free(connections[i]);
    }
    free(connections);
    return 0;
}
