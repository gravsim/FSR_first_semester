#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b)) ? (a) : (b)


int smaller(char* a, char* b, int len_a, int len_b) {
    int i = 0;
    int min_len = min(len_a, len_b);
    while (i < min_len && a[i] == b[i]) {
        i++;
    }
    if (i < min_len) {
        if (a[i] < b[i]) {
            return 1;
        }
        return 0;
    }
    return len_a < len_b;
}


int swap_char_pointers(char** a, char** b) {
    if (!a || !b) {
        return -1;
    }
    char* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_int(int* a, int* b) {
    if (!a || !b) {
        return -1;
    }
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


void quick_sort(char** array, int* lengths, int size, int down, int up) {
    if (down >= up) {
        return;
    }
    int pivot_index = (up + down) / 2;
    char* pivot = array[pivot_index];
    int left = down;
    int right = up;
    while (left <= right) {
        while (smaller(array[left], pivot, lengths[left], lengths[pivot_index])) {
            left++;
        }
        while (smaller(pivot, array[right], lengths[left], lengths[pivot_index])) {
            right--;
        }
        if (left <= right) {
            swap_char_pointers(array + left, array + right);
            swap_int(lengths + left, lengths + right);
            left++;
            right--;
        }
    }
    quick_sort(array, lengths, size, down, right);
    quick_sort(array, lengths, size, left, up);
}


int main(void) {
    int max_length = 100;
    int amount = 0;
    int i;
    char** strings = calloc(max_length, sizeof(char*));
    for (i = 0; i < max_length; i++) {
        strings[i] = calloc(max_length, sizeof(char));
    }
    int* lengths = calloc(max_length, sizeof(int));
    while (scanf("%c", strings[amount] + lengths[amount]) != EOF) {
        if (strings[amount][lengths[amount]] == '\n') {
            amount++;
        } else {
            lengths[amount]++;
        }
    }
    quick_sort(strings, lengths, amount, 0, amount - 1);
    for (i = 0; i < amount; i++) {
        printf("%s", strings[i]);
    }
    free(lengths);
    for (i = 0; i < max_length; i++) {
        free(strings[i]);
    }
    free(strings);
    return 0;
}
