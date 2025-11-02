#include <stdio.h>
#include <stdlib.h>


struct Scales {
    int* left_weights;
    int* right_weights;

    int left_size;
    int right_size;
};


void print_scales(int size, int* scales) {
    if (size == 0) {
        printf("0 ");
        return;
    }
    int i = 0;
    while (i < size) {
        printf("%i ", scales[i]);
        i++;
    }
    printf("\n");
}


int put_on_sides(int side,
                int N,
                int i,
                int* weights,
                struct Scales* scales,
                int left_sum,
                int right_sum) {
    printf("\nRight sum: %d Left sum: %d \n", right_sum, left_sum);
    if (left_sum == right_sum) {
        return 1;
    }
    if (i >= N) {
        // printf("Out of weights\n");
        return 0;
    }
    switch (side) {
        case 0:
            left_sum += weights[i];
            break;
        case 1:
            right_sum += weights[i];
            break;
    }
    
    printf("\n");
    if (put_on_sides(0, N, i + 1, weights, scales, left_sum, right_sum)) {
        scales->left_weights[scales->left_size] = weights[i];
        (scales->left_size)++;
        print_scales(scales->right_size, scales->right_weights);
        print_scales(scales->left_size, scales->left_weights);
        printf("\n");
        return 1;
    }
    if (put_on_sides(1, N, i + 1, weights, scales, left_sum, right_sum)) {
        scales->right_weights[scales->right_size] = weights[i];
        (scales->right_size)++;
        print_scales(scales->right_size, scales->right_weights);
        print_scales(scales->left_size, scales->left_weights);
        printf("\n");
        return 1;
    }
}


int main(void) {
    int K_weight;
    int N;
    scanf("%i %i", &K_weight, &N);
    // printf("N: %i\n", N);
    int* weights = (int*)calloc(N, sizeof(int));
    struct Scales* scales = (struct Scales*)malloc(sizeof(struct Scales));
    
    scales->left_weights = (int*)calloc(N, sizeof(int));
    scales->right_weights = (int*)calloc(N, sizeof(int));

    scales->left_size = 0;
    scales->right_size = 0;
    int i;
    for (i = 0; i < N; i++) {
        scanf("%i", &weights[i]);
    }
    if (put_on_sides(0, N, 0, weights, scales, K_weight, 0) ||
    put_on_sides(1, N, 0, weights, scales, K_weight, 0)) {
        print_scales(scales->right_size, scales->right_weights);
        print_scales(scales->left_size, scales->left_weights);
    } else {
        printf("-1");
    }
    free(weights);
    free(scales->left_weights);
    free(scales->right_weights);
    free(scales);
    return 0;
}
