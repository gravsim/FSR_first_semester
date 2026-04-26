#include <stdio.h>
#include <stdlib.h>


typedef struct vec2 {
    int x;
    int y;
    int index;
} vec2;


int swap_vec2(vec2 *a, vec2 *b) {
    if (!a || !b) {
        return -1;
    }
    vec2 tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int vec2_smaller(vec2 a, vec2 b) {
    if (a.x != b.x) {
        return a.x < b.x;
    }
    if (a.y != b.y) {
        return a.y > b.y;
    }
    return 0;
}


void vec2_quick_sort(vec2 *array, int size, int down, int up) {
    if (down >= up) {
        return;
    }
    vec2 pivot = array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (vec2_smaller(array[left], pivot)) {
            left++;
        }
        while (vec2_smaller(pivot, array[right])) {
            right--;
        }
        if (left <= right) {
            swap_vec2(array + left, array + right);
            left++;
            right--;
        }
    }
    vec2_quick_sort(array, size, down, right);
    vec2_quick_sort(array, size, left, up);
}


int main(void) {
    int segments_amount;
    int i;
    scanf("%d", &segments_amount);
    int a;
    int b;
    vec2* segments = calloc(segments_amount, sizeof(vec2));
    for (i = 0; i < segments_amount; i++) {
        scanf("%d %d", &a, &b);
        segments[i] = (vec2){a, b, i};
    }
    vec2_quick_sort(segments, segments_amount, 0, segments_amount - 1);
    int* answers = calloc(segments_amount, sizeof(int));
    vec2* stack = calloc(segments_amount, sizeof(vec2));
    int top = 0;
    vec2 top_element;
    for (i = 0; i < segments_amount; i++) {
        while (top > 0 && segments[i].y > stack[top - 1].y) {
            top--;
        }
        if (top > 0) {
            top_element = stack[top - 1];
            answers[segments[i].index] = top_element.index + 1;
        }
        stack[top++] = segments[i];
    }
    for (i = 0; i < segments_amount; i++) {
        printf("%d ", answers[i]);
    }
    free(answers);
    free(stack);
    return 0;
}
