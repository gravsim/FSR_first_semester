#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-300
#define AREA_DIFFERENCE 1e-11


typedef struct vec2 {
    double x;
    double y;
} vec2;


int double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
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


int get_polygon_area(long polygon_size, vec2* polygon, double* area) {
    if (polygon == NULL) {
        return -1;
    }
    int i;
    int next;
    *area = 0;
    for (i = 0; i < polygon_size; i++) {
        next = (i + 1) % polygon_size;
        *area += polygon[i].x * polygon[next].y
                -
                polygon[i].y * polygon[next].x;
    }
    *area = fabs(*area) / 2;
    return 1;
}


int swap_vec2_pointers(vec2** a, vec2** b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    vec2* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_double(double* a, double* b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    double tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_long(long* a, long* b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    long tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}




int in_triangle(vec2 v1, vec2 v2, vec2 v3, vec2 point) {
    int sign1 = vectors_sign(point, v1, v2);
    int sign2 = vectors_sign(point, v2, v3);
    int sign3 = vectors_sign(point, v3, v1);
    return (sign1 >= 0 && sign2 >= 0 && sign3 >= 0)
            ||
            (sign1 <= 0 && sign2 <= 0 && sign3 <= 0);
}


int in_polygon(long polygon_size, vec2* polygon, vec2 point) {
    if (vectors_sign(point, polygon[0], polygon[1]) < 0) {
        return 0;
    }
    if (vectors_sign(point, polygon[0], polygon[polygon_size - 1]) > 0) {
        return 0;
    }
    int left = 1;
    int right = polygon_size - 1;
    int middle;
    while (right - left > 1) {
        middle = (right + left) / 2;
        if (vectors_sign(point, polygon[0], polygon[middle]) >= 0) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return in_triangle(polygon[0], polygon[left], polygon[right], point);
}


double get_left_x(vec2* polygon, int polygon_size) {
    int i;
    double left_x = polygon[0].x;
    for (i = 0 ; i < polygon_size; i++) {
        if (polygon[i].x < left_x){
            left_x = i;
        }
    }
    return left_x;
}


double get_right_x(vec2* polygon, int polygon_size) {
    int i;
    double right_x = polygon[0].x;
    for (i = 0 ; i < polygon_size; i++) {
        if (polygon[i].x > right_x){
            right_x = i;
        }
    }
    return right_x;
}


int get_intersection(vec2 point1, vec2 point2, vec2* intersection, double sweeping_line_x) {
    double x1 = point1.x;
    double x2 = point2.x;
    double y1 = point1.y;
    double y2 = point2.y;

    double t = (sweeping_line_x - x1) / (x2 - x1);
    if (t >= 0 && t <= 1) {
        *intersection = (vec2){x1 + t * (x2 - x1), y1 + t * (y2 - y1)};
        return 1;
    }
    return 0;
}


int build_sector(
    vec2* sector,
    int* sector_size,
    vec2* polygon,
    int polygon_size,
    double sweeping_line_x,
    vec2** cuts,
    int sector_index
    ) {

    *sector_size = 0;
    vec2 sweeping_line_start = (vec2){sweeping_line_x, 0};
    vec2 sweeping_line_end = (vec2){sweeping_line_x, 1};
    int i;
    for (i = 0; i < polygon_size; i++) {
        if (vectors_sign(polygon[i], sweeping_line_start, sweeping_line_end) > 0) {
            sector[(*sector_size)++] = polygon[0];
        }
    }
    vec2 intersection;
    int j = 0;
    for (i = 0; i < polygon_size; i++) {
        if (get_intersection(polygon[i], polygon[i + 1], &intersection, sweeping_line_x) > 0) {
            sector[(*sector_size)++] = intersection;
            cuts[sector_index] = intersection
        }
    }
    return 1;
}



int get_right_down(vec2* hull, int hull_size) {
    int i;
    int right = 0;
    for (i = 0 ; i < hull_size; i++) {
        if (hull[i].x > hull[right].x
                ||
                (double_equal(hull[i].x, hull[right].x)
                 &&
                 hull[i].y < hull[right].y)){
            right = i;
                 }
    }
    return right;
}


int vec2_smaller(vec2 a, vec2 b, vec2 base) {
    vec2 diff1 = subtract(a, base);
    vec2 diff2 = subtract(b, base);
    double cross = cross2(diff1, diff2);
    if (cross > 0) {
        return 1;
    }
    return 0;
}


int swap_vec2(vec2* a, vec2* b) {
    if (!a || !b) {
        return -1;
    }
    vec2 tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


void quick_sort(vec2* main_array, int size, int down, int up, vec2 base) {
    if (down >= up) {
        return;
    }
    vec2 pivot = main_array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (vec2_smaller(main_array[left], pivot, base)) {
            left++;
        }
        while (vec2_smaller(pivot, main_array[right], base)) {
            right--;
        }
        if (left <= right) {
            swap_vec2(main_array + left, main_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, size, down, right, base);
    quick_sort(main_array, size, left, up, base);
}


int sort_sector(vec2* sector, int sector_size) {
    if (sector == NULL) {
        return -1;
    }
    int right_down = get_right_down(sector, sector_size);
    swap_vec2(&sector[0], &sector[right_down]);
    quick_sort(sector + 1, sector_size - 1, 0, sector_size - 2, sector[0]);
    return 1;
}


int main(void) {
    long jury_amount;
    long polygon_size;
    long i;
    long j;
    scanf("%ld %ld", &jury_amount, &polygon_size);
    vec2* polygon = calloc(polygon_size, sizeof(vec2));
    scanf("%ld", &polygon_size);
    for (i = 0; i < polygon_size; i++) {
        scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
    }
    double total_area;
    double local_area;
    get_polygon_area(polygon_size, polygon, &total_area);

    double slice_area = total_area / jury_amount;
    double sweeping_line_x;
    double right_x = get_right_x(polygon, polygon_size);
    double left_x = get_left_x(polygon, polygon_size);
    vec2* sector = calloc(polygon_size, sizeof(vec2));
    int sector_size;
    vec2** cuts = calloc(jury_amount - 1, sizeof(vec2*));
    for (i = 0; i < jury_amount - 1; i++) {
        cuts[i] = calloc(2, sizeof(vec2));
    }
    for (i = 0; i < jury_amount; i++) {
        while (fabs(local_area - slice_area) > AREA_DIFFERENCE) {
            sweeping_line_x = (right_x + left_x) / 2;
            build_sector(sector, &sector_size, polygon, polygon_size, sweeping_line_x, cuts, i);
            sort_sector(sector, sector_size);
            get_polygon_area(sector_size, sector, &local_area);
            if (local_area > slice_area) {
                left_x = sweeping_line_x;
            } else {
                right_x = sweeping_line_x;
            }
        }
    }
    free(polygon);
    return 0;
}
