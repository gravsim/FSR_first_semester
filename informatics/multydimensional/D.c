#include <stdio.h>
#include <stdlib.h>


int find_max_area(int heights[], int M) {
    int stack[5000]; 
    int top = -1;
    int area;
    int max_area = 0;
    int i = 0;
    int h;
    int height_rect;
    int width_rect;
    while (i <= M) {
        h = (i == M) ? 0 : heights[i]; 
        if (top != -1 && h < heights[stack[top]]) {
            height_rect = heights[stack[top]];
            top--;
            width_rect = (top == -1) ? i : (i - stack[top] - 1);
            area = height_rect * width_rect;
            if (area > max_area) {
                max_area = area;
            }
        }
        else {
            stack[top + 1] = i;
            top++;
            i++;
        }
    }
    return max_area;
}


int main() {
    int N;
    int M;
    int number;
    scanf("%d %d", &N, &M);
    int i, j;
    int *heights = (int*)calloc(M, sizeof(int));
    int max_area = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &number);
            if (number == 1) {
                heights[j] = 0;
            } else {
                heights[j] += 1;
            }
        }
        int area = find_max_area(heights, M);
        if (area > max_area)
            max_area = area;
        }
    printf("%d", max_area);
    return 0;
}
