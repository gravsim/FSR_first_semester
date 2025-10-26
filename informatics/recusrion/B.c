#include <stdio.h>
#include <stdlib.h>


void print_array(int N, int* array) {
    int i;
    for (i = 0; i < N; i++) {
        if (array[i]) {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}


void check_previous(int i, int* array) {
    array[i]--;
    array[i - 1]++;
    if (array[i - 2] < array[i - 1]) {
        check_previous(i - 1, array);
    }
}


void separate(int N, int* array) {
    int i;
    print_array(N, array);
    for (i = N; i >= 0; i--) {
        if (array[i] > 0 && i > 0 && array[i - 1] >= array[i]) {
            check_previous(i, array);
            separate(N, array);
        }
    }
}


void fill_array(int N, int* array) {
    int i;
    for (i = 0; i < N; i++) {
        array[i] = 1;
    }
}


int main() {
    int N;
    scanf("%d", &N);
    int* array = (int*)calloc(N, sizeof(int));
    fill_array(N, array);
    separate(N, array);
    return 0;
}
