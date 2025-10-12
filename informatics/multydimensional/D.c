#include <stdio.h>


int find_max_area(int heights[], int M) {
    int i, j;
    int min = heights[0];
    int area = 0;
    int cut_heights[5000] = {0};
    int slice_heights[1000] = {0};
    printf("\nHeights: ");
    for (i = 0; i < M; i++) {
        printf("%d ", heights[i]);
        if (heights[i] < min) {
            min = heights[i];
        }
    }
    printf("END\n");
    int max_area = min * M;
    for (i = 0; i < M; i++) {
        cut_heights[i] = heights[i] - min;
    }

    for (i = 0; i < M; i++) {
        j = i;
        while (j < M && cut_heights[j] >= cut_heights[i]) {
            j++;
        }
        if (cut_heights[j] < cut_heights[i]) {
            int k;
            for (k = 0; k < (j - i); k++) {
                slice_heights[k] = cut_heights[i + k];
            }
            area = find_max_area(slice_heights, j - i);
        } else {
            area = (cut_heights[i] + min) * (j - i + 1);
        }
        
        printf("\nArea: %d. ", area);
        if (area > max_area) {
            max_area = area;
        }
    }
    printf("\nMax area: %d. ", max_area);
    return max_area;
}


int main() {
    int N;
    int M;
    int number;
    scanf("%d %d", &N, &M);
    int heights[5000] = {0};
    int i, j;
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
