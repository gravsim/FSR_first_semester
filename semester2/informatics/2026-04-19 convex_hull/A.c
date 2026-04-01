#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-300


typedef struct vec2 {
    double x;
    double y;
} vec2;


int double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


double get_norm(vec2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
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


int double_sign(double a) {
    return (a > EPSILON) - (a < -EPSILON);
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    return double_sign(cross2(edge, diff));
}


int point_on_segment(vec2 A, vec2 B, vec2 point) {
    return double_equal(distance(A, point) + distance(B, point), distance(A, B));
}


int main(void) {
    long n;
    vec2 point;
    scanf("%ld %lf %lf", &n, &point.x, &point.y);
    vec2* vertices = calloc(n, sizeof(vec2));
    long i;
    long intersections_amount = 0;
    vec2 ray_end = (vec2){10000, point.y + 10};
    long end;
    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
    }
    i = 0;
    end = 1;
    while (i < n && !point_on_segment(vertices[i], vertices[end], point)) {
        end = (i + 1) % n;
        if (vectors_sign(vertices[i], point, ray_end)
            !=
            vectors_sign(vertices[end], point, ray_end)
            &&
            vectors_sign(point, vertices[i], vertices[end])
            !=
            vectors_sign(ray_end, vertices[i], vertices[end])
            ) {
                intersections_amount++;
        }
        i++;
    }
    if (i < n || intersections_amount % 2 == 1) {
        printf("YES");
    } else {
        printf("NO");
    }
    free(vertices);
    return 0;
} 