#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-20


double norm(double* vector) {
    return sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
}


double distance(double vector1[2], double vector2[2]) {
    double difference[2] = {vector1[0] - vector2[0], vector1[1] - vector2[1]};
    return norm(difference);
}


double double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


void swap(double* a, double* b) {
    double* tmp = a;
    *a = *b;
    *b = *tmp;
}


void check_points(double x1, double x2, double* max, double* min) {
    if (x1 < x2) {
        *max = x2;
        *min = x1;
    } else {
        *max = x1;
        *min = x2;
    }
}


int main(void) {
    double* A = malloc(2 * sizeof(double));
    double* B = malloc(2 * sizeof(double));
    double* point = malloc(2 * sizeof(double));
    scanf("%lf %lf %lf %lf %lf %lf", point, point + 1, A, A + 1, B, B + 1);
    if (double_equal(distance(A, point) + distance(B, point), distance(A, B))) {
        printf("YES");
    } else {
        printf("NO");
    }
    free(A);
    free(B);
    free(point);
    return 0;
}
