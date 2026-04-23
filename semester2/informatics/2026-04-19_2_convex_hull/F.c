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


vec2 add(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x + vector2.x, vector1.y + vector2.y};
}


vec2 multiply(vec2 vector, double k) {
    return (vec2){k * vector.x, k * vector.y};
}


double distance(vec2 vector1, vec2 vector2) {
    return get_norm(subtract(vector2, vector1));
}


vec2 normalize(vec2 vector) {
    double norm = get_norm(vector);
    if (double_equal(norm, 0.)) {
        return vector;
    }
    return (vec2){vector.x / norm, vector.y / norm};
}


double dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}


double get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}


double get_sin(vec2 origin, vec2 point1, vec2 point2) {
    double cos = get_cos(subtract(point1, origin), subtract(point2, origin));
    return sqrt((1 - cos) / 2);
}


vec2 get_new_point(vec2 origin, vec2 point1, vec2 point2, double radius) {
    vec2 direction1 = normalize(subtract(point1, origin));
    vec2 direction2 = normalize(subtract(point2, origin));
    vec2 bisector = normalize(add(direction1, direction2));
    vec2 point = add(origin, multiply(bisector, radius / get_sin(origin, point1, point2)));
    return point;
}


int get_centers(int polygon_size, vec2* inner_polygon, vec2* center1, vec2* center2) {
    if (inner_polygon == NULL
        ||
        center1 == NULL
        ||
        center2 == NULL) {
            return -1;
    }
    int i;
    int j;
    double max_distance = 0;
    for (i = 0; i < polygon_size; i++) {
        for (j = i + 1; j < polygon_size; j++) {
            if (distance(inner_polygon[i], inner_polygon[j]) > max_distance) {
                max_distance = distance(inner_polygon[i], inner_polygon[j]);
                *center1 = inner_polygon[i];
                *center2 = inner_polygon[j];
            }
        }
    }
    return 1;
}


int build_inner_polygon(
    int polygon_size,
    vec2* polygon,
    vec2* inner_polygon,
    int radius
    ) {
        if (polygon == NULL || inner_polygon == NULL) {
            return -1;
        }
        int i;
        int next1;
        int next2;
        for (i = 0; i < polygon_size; i++) {
            next1 = (i + 1) % polygon_size;
            next2 = (i + 2) % polygon_size;
            inner_polygon[i] = get_new_point(polygon[next1], polygon[i], polygon[next2], radius);
        }
        return 1;
}


int main(void) {
    int radius;
    int polygon_size;
    int i;
    scanf("%d %d", &polygon_size, &radius);
    vec2* polygon = calloc(polygon_size, sizeof(vec2));
    vec2* inner_polygon = calloc(polygon_size, sizeof(vec2));
    for (i = 0; i < polygon_size; i++) {
        scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
    }
    build_inner_polygon(polygon_size, polygon, inner_polygon, radius);
    vec2 center1 = (vec2){0, 0};
    vec2 center2 = (vec2){0, 0};
    get_centers(polygon_size, inner_polygon, &center1, &center2);
    printf("%.4lf %.4lf %.4lf %.4lf\n",
                center1.x,
                center1.y,
                center2.x,
                center2.y);
    free(polygon);
    free(inner_polygon);
    return 0;
}
