#include <stdio.h>
#include <stdlib.h>
#include <math.h>




void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void quick_sort(long long* main_array, long long* side_array, long long size){
    /*
         Слегка измененный QuickSort.
         Над побочным массивом (в нашем случае indices) производим все те же операции,
         что и над главным массивом, который мы сортируем. Это нужно, чтобы запомнить
         исходный порядок элементов в главном массиве, и в дальнейшем его восстановить.
    */
    long long down = 0;
    long long up = size - 1;
    long long pivot = main_array[size / 2];
    if (size > 1){
        while (down <= up){
            while (main_array[down] < pivot) down++;
            while (pivot < main_array[up]) up--;
            if (down <= up){
                swap(&main_array[down], &main_array[up]);
                swap(&side_array[down], &side_array[up]);
                down++;
                up--;
            }
        }
        quick_sort(main_array, side_array, up + 1);
        quick_sort(main_array + down, side_array + down, size - down);
    }
}



int in_rectangle(double X, double Y, double x, double y) {
    if (X > 0) {
        if (Y > 0) {
            return x >= 0 && x <= X && y >= 0 && y <= Y;
        }
        return x >= 0 && x <= X && y <= 0 && y >= Y;
    }
    if (Y > 0) {
        return x <= 0 && x >= X && y >= 0 && y <= Y;
    }
    return x <= 0 && x >= X && y <= 0 && y >= Y;
}


void find_intersection(double* line1, double* line2, double* x, double* y) {
    *x = (line2[1] / line1[1] * line1[2] - line2[2]) / (line2[0] - line2[1] / line1[1] * line1[0]);
    *y = (line2[0] / line1[0] * line1[2] - line2[2]) / (line2[1] - line2[0] / line1[0] * line1[1]);
}


int main(void) {
    double X;
    double Y;
    int N;
    scanf("%lf %lf %d", &X, &Y, &N);
    double** lines = calloc(N + 4, sizeof(double*));
    double** points = calloc(N, sizeof(double*));
    double* storage = calloc(N, sizeof(double));
    int* indices = calloc(N, sizeof(int));
    int polygons = 0;
    int i;
    int j;
    double x;
    double y;
    for (i = 0; i < N; i++) {
        lines[i] = calloc(3, sizeof(double));
        points[i] = calloc(100, sizeof(double));
        scanf("%lf %lf %lf", &lines[i][0], &lines[i][1], &lines[i][2]);
    }
    lines[i][0] = 1.0;
    lines[i][1] = 0.0;
    lines[i][2] = 0.0;
    i++;
    lines[i][0] = 0.0;
    lines[i][1] = 1.0;
    lines[i][2] = 0.0;
    i++;
    lines[i][0] = -1.0;
    lines[i][1] = 0.0;
    lines[i][2] = X;
    i++;
    lines[i][0] = 0.0;
    lines[i][1] = -1.0;
    lines[i][2] = Y;
    i++;
    N = i;
    int size = 0;
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            find_intersection(lines[i], lines[j], &x, &y);
            if (in_rectangle(X, Y, x, y)) {
                points[i][size] = x;
                points[j][size] = x;
                storage[size] = x;
                size++;
            }
        }
    }
    // Сделали массив, показывающий какие точки лежат на каких прямых.
    quick_sort(storage, indices, N);
    printf("%d", polygons);
    for (i = 0; i < N; i++) {
        free(lines[i]);
    }
    free(lines);
    return 0;
}
