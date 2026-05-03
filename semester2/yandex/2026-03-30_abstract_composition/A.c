#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define PRECISION 1e-10
#define BEGINNING 0
#define CROSS 1
#define END 2


typedef struct BST_node {
    int line_index;
    struct BST_node* left;
    struct BST_node* right;
} BST_node;


typedef struct vec2 {
    double x;
    double y;
} vec2;


typedef struct Heap_node {
    vec2 start;
    vec2 end;
    int index;
} Heap_node;


int double_equal(double a, double b) {
    return fabs(a - b) < PRECISION;
}


int swap_int(int* a, int* b) {
    if (!a || !b) {
        return -1;
    }
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


double get_y(Heap_node* rectangles, int line_index) {
    return rectangles[line_index].start.y;
}


BST_node* BST_new_node(int line_index) {
    BST_node* new_node = malloc(sizeof(BST_node));
    new_node->line_index = line_index;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


int less_y(Heap_node* rectangles, int line1, int line2) {
    double y1 = get_y(rectangles, line1);
    double y2 = get_y(rectangles, line2);
    if (double_equal(y1, y2)) {
        if (line1 < line2) {
            return 1;
        }
    }
    return y1 < y2;
}


BST_node* BST_push(
    Heap_node* rectangles,
    BST_node* root_p,
    int line_index
    ) {
    if (!root_p) {
        return BST_new_node(line_index);
    }
    if (line_index == root_p->line_index) {
        return root_p;
    }
    if (less_y(rectangles, line_index, root_p->line_index)) {
        root_p->left = BST_push(rectangles, root_p->left, line_index);
    } else {
        root_p->right = BST_push(rectangles, root_p->right, line_index);
    }
    return root_p;
}


int BST_free_node(BST_node** leaf_pp) {
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


int BST_low_neighbour(
    Heap_node* rectangles,
    BST_node* root_p,
    int line_index
    ) {
    int biggest_line_index = -1;
    while (root_p) {
        if (less_y(rectangles, line_index, root_p->line_index)) {
            root_p = root_p->right;
        } else {
            biggest_line_index = root_p->line_index;
            root_p = root_p->left;
        }
    }
    return biggest_line_index;
}


int BST_high_neighbour(
    Heap_node* rectangles,
    BST_node* root_p,
    int line_index
    ) {
    int lowest_line_index = -1;
    while (root_p) {
        if (less_y(rectangles, line_index, root_p->line_index)) {
            lowest_line_index = root_p->line_index;
            root_p = root_p->left;
        } else {
            root_p = root_p->right;
        }
    }
    return lowest_line_index;
}



BST_node** BST_find_right_min(BST_node** node) {
    if (!*node) {
        return NULL;
    }
    while ((*node)->right) {
        node = &(*node)->right;
    }
    return node;
}


BST_node** BST_search_node(
    Heap_node* rectangles,
    BST_node** current,
    int line_index
    ) {
    while (*current && (*current)->line_index != line_index) {
        if (less_y(rectangles, line_index, (*current)->line_index)) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    return current;
}


int BST_delete_node(BST_node** node_pp) {
    if (!node_pp || !*node_pp) {
        return 0;
    }
    BST_node* tmp = *node_pp;
    if (!(*node_pp)->right && !(*node_pp)->left) {
        free(tmp);
        *node_pp = NULL;
        return 1;
    }
    if (!(*node_pp)->right) {
        *node_pp = (*node_pp)->left;
        free(tmp);
        return 1;
    }
    if (!(*node_pp)->left) {
        *node_pp = (*node_pp)->right;
        free(tmp);
        return 1;
    }
    BST_node** descendant = BST_find_right_min(&(*node_pp)->left);
    (*node_pp)->line_index = (*descendant)->line_index;
    return BST_delete_node(descendant);
}



int BST_swap_nodes(
    Heap_node* rectangles,
    BST_node** root_p,
    int index1,
    int index2
    ) {
    BST_node** node1 = BST_search_node(rectangles, root_p, index1);
    BST_node** node2 = BST_search_node(rectangles, root_p, index2);
    swap_int(&(*node1)->line_index, &(*node2)->line_index);
    return 1;
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x)
        &&
        double_equal(vector1.y, vector2.y);
}


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


int is_smaller(Heap_node a, Heap_node b) {
    if (a.start.x < b.start.x - PRECISION) {
        return 1;
    }
    if (a.start.x > b.start.x + PRECISION) {
        return 0;
    }
    if (a.start.y < b.start.y - PRECISION) {
        return 1;
    }
    if (a.start.y > b.start.y + PRECISION) {
        return 0;
    }
    return a.index < b.index;
}


int Heap_sift_up(Heap* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0
        &&
        is_smaller(heap->values[index], heap->values[parent])
        ) {
        Heap_swap_nodes(heap->values + index, heap->values + parent);
        index = parent;
        parent = (index - 1) / 2;
    }
    return 0;
}


int Heap_sift_down(Heap* heap, int index) {
    int next = index;
    if (2 * index + 1 < heap->size
        &&
        is_smaller(heap->values[2 * index + 1], heap->values[next])
        ) {
        next = 2 * index + 1;
    }
    if (2 * index + 2 < heap->size
        &&
        is_smaller(heap->values[2 * index + 2], heap->values[next])
        ) {
        next = 2 * index + 2;
    }
    if (next != index) {
        Heap_swap_nodes(&heap->values[index], &heap->values[next]);
        return Heap_sift_down(heap, next);
    }
    return next;
}


int Heap_push(Heap* heap, double Ax, double Ay, double Bx, double By, int index) {
    if (Heap_is_full(heap)) {
        Heap_expand(heap);
    }
    heap->values[heap->size].start.x = Ax;
    heap->values[heap->size].start.y = Ay;
    heap->values[heap->size].end.x = Bx;
    heap->values[heap->size].end.y = By;
    heap->values[heap->size].index = index;
    Heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int Heap_pop_minimum(Heap* heap, Heap_node* value) {
    *value = heap->values[0];
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



int get_area(
    int** cross_matrix,
    double* area,
    Heap_node* rectangles,
    int index1,
    int index2
    ) {
    double height;
    double width;
    int up;
    int down;
    int right;
    int left;
    if (index1 != -1
        &&
        index2 != -1
        &&
        index1 != index2
        ) {
        if (rectangles[index1].start.y > rectangles[index2].start.y) {
            up = index1;
            down = index2;
        } else {
            up = index2;
            down = index1;
        }
        if (rectangles[index1].start.x > rectangles[index2].start.x) {
            right = index1;
            left = index2;
        } else {
            right = index2;
            left = index1;
        }
        height = rectangles[up].start.y - rectangles[down].end.y;
        width = rectangles[right].start.x - rectangles[left].end.x;
        *area += height * width;
    }
    return 0;
}


int algorithm(
    int** cross_matrix,
     double* area,
     Heap_node* rectangles,
     Heap** heap,
     BST_node** root_p
    ) {
    Heap_node rectangle;
    int low_neighbour;
    int high_neighbour;
    BST_node** found;
    while (!Heap_is_empty(*heap)) {
        Heap_pop_minimum(*heap, &rectangle);
        *root_p = BST_push(rectangles, *root_p, rectangle.index);
        low_neighbour = BST_low_neighbour(rectangles, *root_p, rectangle.index);
        high_neighbour = BST_high_neighbour(rectangles, *root_p, rectangle.index);
        get_area(cross_matrix,
            area,
            rectangles,
            rectangle.index,
            low_neighbour);
        get_area(cross_matrix,
            area,
            rectangles,
            rectangle.index,
            high_neighbour);
        found = BST_search_node(rectangles, root_p, rectangle.index);
        if (found && *found) {
            BST_delete_node(found);
        }
    }
    return 1;
}


int main(void) {
    int rectangles_amount;
    scanf("%d", &rectangles_amount);
    int index;
    double Ax;
    double Ay;
    double Bx;
    double By;
    int i;
    BST_node* root = NULL;
    Heap* heap;
    double area = 0;
    Heap_node* rectangles = calloc(rectangles_amount, sizeof(Heap_node));
    int** cross_matrix = calloc(rectangles_amount, sizeof(int*));
    for (i = 0; i < rectangles_amount; i++) {
        cross_matrix[i] = calloc(rectangles_amount, sizeof(int));
    }
    Heap_init(&heap);
    double height;
    double width;
    for (index = 0; index < rectangles_amount; index++) {
        scanf("%lf %lf %lf %lf", &Ax, &Ay, &width, &height);
        Bx = Ax + width;
        By = Ay + height;
        area += height * width;
        rectangles[index].index = index;
        rectangles[index].start.x = Ax;
        rectangles[index].start.y = Ay;

        rectangles[index].end.x = Bx;
        rectangles[index].end.y = By;

        Heap_push(heap, Ax, Ay, Bx, By, index);
    }
    algorithm(cross_matrix, &area, rectangles, &heap, &root);
    printf("%lf\n", area);
    free(rectangles);
    BST_free_root(&root);
    free(heap->values);
    free(heap);
    return 0;
}
