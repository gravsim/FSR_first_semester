#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct vec2 {
    double x;
    double y;
} vec2;


double get_norm(vec2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double distance(vec2 vector1, vec2 vector2) {
    return get_norm(subtract(vector2, vector1));
}


typedef struct DSU_node {
    struct DSU_node* parent;
    double sum;
    int rang;
} DSU_node;


typedef struct Edge {
    int from;
    int to;
    double weight;
} Edge;


DSU_node* make_set(double sum) {
    DSU_node* tmp = malloc(sizeof(DSU_node));
    tmp->sum = sum;
    tmp->parent = tmp;
    tmp->rang = 1;
    return tmp;
}


DSU_node* find_set(DSU_node* node) {
    if (node->parent == node) {
        return node;
    }
    return node->parent = find_set(node->parent);
}


DSU_node* union_set(DSU_node* node1, DSU_node* node2, double sum) {
    if (node1 == NULL || node2 == NULL) {
        return NULL;
    }
    node1 = find_set(node1);
    node2 = find_set(node2);
    if (node1 == node2) {
        return node1;
    }
    if (node1->rang < node2->rang) {
        DSU_node* tmp = node1;
        node1 = node2;
        node2 = tmp;
    }
    node2->parent = node1;
    if (node1->rang == node2->rang) {
        node1->rang++;
    }
    node1->sum += node2->sum + sum;
    return node1;
}


int swap_edge(Edge* a, Edge* b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    Edge tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


void quick_sort(Edge* array, int down, int up) {
    if (down >= up) {
        return;
    }
    Edge pivot = array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (array[left].weight < pivot.weight) {
            left++;
        }
        while (pivot.weight < array[right].weight) {
            right--;
        }
        if (left <= right) {
            swap_edge(array + left, array + right);
            left++;
            right--;
        }
    }
    quick_sort(array, down, right);
    quick_sort(array, left, up);
}


double Kruskal(Edge* edges, int components, DSU_node** nodes) {
    if (edges == NULL || nodes == NULL) {
        return -1;
    }
    int i = 0;
    int E = components * (components - 1) / 2;
    quick_sort(edges, 0, E - 1);
    while (components > 1) {
        if (find_set(nodes[edges[i].from]) != find_set(nodes[edges[i].to])) {
            union_set(nodes[edges[i].from], nodes[edges[i].to], edges[i].weight);
            components--;
        }
        i++;
    }
    return find_set(nodes[0])->sum;
}


int main(void) {
    int N;
    int i;
    int j;
    double sector_x;
    double sector_y;
    scanf("%lf %lf %d", &sector_y, &sector_x, &N);
    N++;
    vec2* points = calloc(N, sizeof(vec2));
    DSU_node** nodes = calloc(N, sizeof(DSU_node*));
    int E = N * (N - 1) / 2;
    Edge* edges = calloc(E, sizeof(Edge));
    for (i = 0; i < N; i++) {
        nodes[i] = make_set(0);
    }
    int edges_amount = 0;
    for (i = 0; i < N - 1; i++) {
        scanf("%lf %lf", &points[i].y, &points[i].x);
    }
    points[N - 1].x = sector_x / 2;
    points[N - 1].y = sector_y;
    for (i = 0; i < N; i++) {
        for (j = 0; j < i; j++) {
            edges[edges_amount].from = j;
            edges[edges_amount].to = i;
            edges[edges_amount].weight = distance(points[i], points[j]);
            edges_amount++;
        }
    }
    printf("%.6lf", Kruskal(edges, N, nodes));
    for (i = 0; i < N; i++) {
        free(nodes[i]);
    }
    free(nodes);
    free(edges);
    free(points);
    return 0;
}
