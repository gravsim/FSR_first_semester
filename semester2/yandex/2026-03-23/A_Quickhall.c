#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-20


typedef struct vec2 {
    double x;
    double y;
} vec2;


double double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


double get_norm(vec2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


vec2 normalize(vec2 vector) {
    double norm = get_norm(vector);
    if (double_equal(norm, 0.)) {
        return vector;
    }
    return (vec2){vector.x / norm, vector.y / norm};
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double distance(vec2 vector1, vec2 vector2) {
    return get_norm(subtract(vector2, vector1));
}


double cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


double dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}



double get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}


int int_sign(double a) {
    return (a > EPSILON) - (a < -EPSILON);
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    int result = int_sign(cross2(edge, diff));
    return result;
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x)
           &&
           double_equal(vector1.y, vector2.y);
}



double line_distance(vec2 start, vec2 end, vec2 point) {
    double A = start.y - end.y;
    double B = end.x - start.x;
    double C = A * start.x + B * start.y;
    return fabs(A * point.x + B * point.y + C) / sqrt(A * A + B * B);
}



void QuickHall_algorithm(int n, vec2* vertices, vec2* hull, int* hull_size, vec2 vert1, vec2 vert2, int side) {
    int index = -1;
    double max_distance = 0;
    int i;
    double tmp;
    for (i = 0; i < n; i++) {
        tmp = line_distance(vert1, vert2, vertices[i]);
        if (vectors_sign(vertices[i], vert1, vert2) == side
            &&
            tmp > max_distance) {
            index = i;
            max_distance = tmp;
        }
    }
    if (index == -1) {
        hull[(*hull_size)++] = vert1;
        hull[(*hull_size)++] = vert2;
        return;
    }
    QuickHall_algorithm(n, vertices, hull, hull_size, vertices[index], vert1, -vectors_sign(vertices[index], vert1, vert2));
    QuickHall_algorithm(n, vertices, hull, hull_size, vertices[index], vert2, -vectors_sign(vertices[index], vert2, vert1));

}


int main(void) {
    int n;
    scanf("%d", &n);
    vec2* vertices = calloc(n, sizeof(vec2));
    vec2* hull = calloc(n, sizeof(vec2));
    int hull_size = 0;
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
    }
    if (n == 0) {
        free(vertices);
        free(hull);
        return 0;
    }
    if (n == 1) {
        printf("%lf %lf\n", vertices[0].x, vertices[0].y);
        free(vertices);
        free(hull);
        return 0;
    }
    int left = 0;
    for (i = 0; i < n; i++) {
        if (vertices[i].x < vertices[left].x
            ||
            (double_equal(vertices[i].x, vertices[left].x)
             &&
             vertices[i].y > vertices[left].y)){
            left = i;
             }
    }
    int right = 0;
    for (i = 0; i < n; i++) {
        if (vertices[i].x > vertices[right].x
            ||
            (double_equal(vertices[i].x, vertices[right].x)
             &&
             vertices[i].y < vertices[right].y)){
             right = i;
             }
    }
    QuickHall_algorithm(n ,vertices, hull, &hull_size, vertices[left], vertices[right], 1);
    QuickHall_algorithm(n ,vertices, hull, &hull_size, vertices[left], vertices[right], -1);
    for (i = 0; i < hull_size; i++) {
        printf("%lf %lf\n", hull[i].x, hull[i].y);
    }
    free(vertices);
    free(hull);
    return 0;
} 