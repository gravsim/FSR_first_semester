#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-10


typedef struct BST_node {
    int value;
    struct BST_node* left;
    struct BST_node* right;
} BST_node;



BST_node* BST_new_node(int value) {
    /*
        Создаем новый узел.
    */
    BST_node* new_node = malloc(sizeof(BST_node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


BST_node* BST_push(BST_node* root_p, int value) {
    /*
        Добавляем новый лист к дереву.
    */
    if (!root_p) {
        return BST_new_node(value);
    }
    if (value == root_p->value) {
        return root_p;
    }
    if (root_p->value < value) {
        root_p->right = BST_push(root_p->right, value);
    } else {
        root_p->left = BST_push(root_p->left, value);
    }
    return root_p;
}


int BST_free_node(BST_node** leaf_pp) {
    /*
        Освобождаем память узлов дерева. Если есть потомки,
        запускаем освобождение для них.
        Не проверяем leaf_pp == NULL, т.к. это было сделано
        до старта рекурсии для данного узла.
    */
    if ((*leaf_pp)->left) {
        BST_free_node(&(*leaf_pp)->left);
    }
    if ((*leaf_pp)->right) {
        BST_free_node(&(*leaf_pp)->right);
    }
    free(*leaf_pp);
    *leaf_pp = NULL;
    return 1;
}


int BST_free_root(BST_node** root_pp) {
    /*
        Освобождаем память корня дерева. Если есть
        потомки, запускаем освобождение для них.
    */
    if (!root_pp || !*root_pp) {
        return -1;
    }
    if ((*root_pp)->left) {
        BST_free_node(&(*root_pp)->left);
    }
    if ((*root_pp)->right) {
        BST_free_node(&(*root_pp)->right);
    }
    free(*root_pp);
    *root_pp = NULL;
    return 1;
}




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
    return (vec2){vector.x / get_norm(vector), vector.y / get_norm(vector)};
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


int int_sign(double a) {
    if (a < EPSILON) {
        return -1;
    }
    if (a > EPSILON) {
        return 1;
    }
    return 0;
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    int result = int_sign(cross2(edge, diff));
    return result;
}


double get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x) && double_equal(vector1.y, vector2.y);
}


typedef struct Point {
    /*
        type:
        0 - beginning of segment
        1 - end of segment
        2 - intersection of segments
    */
    vec2 coords;
    int line_index;
    int type;
} Point;



typedef struct Heap_node {
    int index;
    Point point;
} Heap_node;


typedef struct Heap {
    int size;
    int capacity;
    Heap_node* values;
} Heap;


int Heap_swap_nodes(Heap_node* a, Heap_node* b) {
    Heap_node tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int Heap_is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


int Heap_is_empty(Heap* heap) {
    return heap->size == 0;
}


void Heap_expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (Heap_node*)realloc(heap->values, heap->capacity * sizeof(Heap_node));
}


int Heap_sift_up(Heap* heap, int index) {
    while (index > 0 && heap->values[index].point.coords.x < heap->values[(index - 1) / 2].point.coords.x) {
        Heap_swap_nodes(heap->values + index, heap->values + (index - 1) / 2);
        index = (index - 1) / 2;
    }
    return 0;
}


int Heap_sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2].point.coords.x < heap->values[max_index].point.coords.x) {
        max_index = 2 * index + 2;
    }
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1].point.coords.x < heap->values[max_index].point.coords.x) {
        max_index = 2 * index + 1;
    }
    if (max_index != index) {
        Heap_swap_nodes(&heap->values[index], &heap->values[max_index]);
        return Heap_sift_down(heap, max_index);
    }
    return max_index;
}


int Heap_push(Heap* heap, int index, double value) {
    if (Heap_is_full(heap)) {
        Heap_expand(heap);
    }
    heap->values[heap->size].point.coords.x = value;
    heap->values[heap->size].index = index;
    Heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int Heap_pop_minimum(Heap* heap, int* index, Point* value) {
    *value = heap->values[0].point;
    *index = heap->values[0].index;
    heap->values[0] = heap->values[--heap->size];
    return Heap_sift_down(heap, 0) + 1;
}


int Heap_init(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 1000;
    (*heap)->values = (Heap_node*)calloc((*heap)->capacity, sizeof(Heap_node));
    return 0;
}





void Bentley_Ottmann_algorithm(Heap* heap, BST_node* root_p) {
    int index;
    Point point;
    while (!Heap_is_empty(heap)) {
        Heap_pop_minimum(heap, &index, &point);
        if (point.type == 0) {
            // Beginning
            BST_push(root_p, point.line_index);
        } else if (point.type == 1) {
            // End
            BST_push(root_p, point.line_index);
        } else {
            // Intersection
        }
    }
}


int main(void) {
    int n;
    int answer = 0;
    vec2* barycenter = malloc(sizeof(vec2));
    scanf("%d %lf %lf", &n, &barycenter->x, &barycenter->y);
    vec2* vertices = calloc(n, sizeof(vec2));
    vec2* convex_vertices = calloc(n, sizeof(vec2));
    int convex_size = 0;
    int i;
    BST_node* root = NULL;
    Heap* heap;
    Heap_init(&heap);
    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
    }
    Bentley_Ottmann_algorithm(heap, root);
    int next;
    vec2 edge;
    vec2 vector;
    double t;

    printf("%d", answer);
    free(barycenter);
    free(vertices);
    free(convex_vertices);
    return 0;
}
