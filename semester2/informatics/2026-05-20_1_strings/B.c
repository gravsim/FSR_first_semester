#include <stdio.h>
#include <stdlib.h>


int smaller(char* a, char* b, int len_a, int len_b) {
    int i = 0;
    int union_len = len_a + len_b;
    char char_a;
    char char_b;
    do {
        if (i < len_a) {
            char_a = a[i];
        } else {
            char_a = b[i % len_a];
        }
        if (i < len_b) {
            char_b = b[i];
        } else {
            char_b = a[i % len_b];
        }
        i++;
    } while (i < union_len && char_a == char_b);
    if (i < union_len) {
        if (char_a < char_b) {
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
    int pivot_length = lengths[pivot_index];
    int left = down;
    int right = up;
    while (left <= right) {
        while (left <= up && smaller(array[left], pivot, lengths[left], pivot_length)) {
            left++;
        }
        while (right >= down && smaller(pivot, array[right], pivot_length, lengths[right])) {
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
    int max_length = 101;
    int amount = 0;
    int i;
    char** strings = calloc(max_length, sizeof(char*));
    for (i = 0; i < max_length; i++) {
        strings[i] = calloc(max_length, sizeof(char));
    }
    int* lengths = calloc(max_length, sizeof(int));
    while (scanf("%c", strings[amount] + lengths[amount]) != EOF) {
        if (strings[amount][lengths[amount]] == '\n') {
            strings[amount][lengths[amount]] = '\0';
            amount++;
        } else {
            lengths[amount]++;
        }
    }
    if (lengths[amount] > 0) {
        strings[amount][lengths[amount]] = '\0';
        amount++;
    }
    quick_sort(strings, lengths, amount, 0, amount - 1);
    for (i = amount - 1; i >= 0; i--) {
        printf("%s", strings[i]);
    }
    free(lengths);
    for (i = 0; i < max_length; i++) {
        free(strings[i]);
    }
    free(strings);
    return 0;
}
