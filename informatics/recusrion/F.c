#include <stdio.h>
#include <stdlib.h>


void fill_square(int start, int stop, int** array) {
    int len = stop - start;
    if (start > 1 && len > 0) {
        array[start][start - 1] = 1;
    }
    if (len > 2) {
        int i;
        for (i = start; i < stop; i++) {
            array[start][i] = 1;
        }
        for (i = start; i < stop; i++) {
            array[i][stop - 1] = 1;
        }
        for (i = start; i < stop; i++) {
            array[stop - 1][i] = 1;
        }
        for (i = start + 2; i < stop; i++) {
            array[i][start] = 1;
        }
        if (start > 1) {
        }
        fill_square(start + 2, stop - 2, array);
    } else if (len == 2) {
        array[start][start] = 1;
        array[start][start + 1] = 1;
        array[start + 1][start + 1] = 1;
    } else if (len == 1) {
        array[start][start] = 1;
    }
}


void print_array(int N, int** array) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d", array[i][j]);  
        }
        free(array[i]);
        printf("\n");
    }
    free(array);
}


void create_array(int N, int** array) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            array[i][j] = 0;
        }
    }
}


int main() {
    int N;
    scanf("%d", &N);
    int** array = (int**)calloc(N, sizeof(int*));
    int i;
    for (i = 0; i < N; i++) {
        array[i] = (int*)calloc(N, sizeof(int));
    }
    create_array(N, array);
    fill_square(0, N, array);
    print_array(N, array);
    return 0;
}
