#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 30001



typedef struct DSU_node {
    struct DSU_node* parent;
    int value;
    int rang;
} DSU_node;


DSU_node* make_set(int value) {
    DSU_node* tmp = malloc(sizeof(DSU_node));
    tmp->value = value;
    tmp->parent = tmp;
    tmp->rang = 1;
    return tmp;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void swap_nodes(DSU_node* node1, DSU_node* node2) {
    DSU_node tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}


DSU_node* find_set(DSU_node* node) {
    if (node->parent == node) {
        return node;
    }
    return node->parent = find_set(node->parent);
}


DSU_node* union_set(DSU_node* node1, DSU_node* node2) {
    node1 = find_set(node1);
    node2 = find_set(node2);
    if (node1->rang < node2->rang) {
        swap_nodes(node1, node2);
    }
    node2->parent = node1;
    if (node1->rang == node2->rang) {
        node1->rang++;
    }
    return node1;
}


int get_MST_weight_Prim(int N, int** adjacency_matrix) {
    /*
        In this program array `previous` is not used. I will keep it
        if in future I will need to construct gotten tree.
    */
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    int w;
    int visited_amount;
    int answer = 0;
    int v;
    int* previous = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[0] = 0;
    int* visited = calloc(N, sizeof(int));
    for (visited_amount = 1; visited_amount < N; visited_amount++) {
        v = get_minimal_weight(distances, visited, N);
        visited[v] = 1;
        for (w = 0; w < N; w++) {
            if (adjacency_matrix[v][w]
            && !visited[w]
            && adjacency_matrix[v][w] < distances[w]) {
                previous[w] = v;
                distances[w] = adjacency_matrix[v][w];
            }
        }
    }
    for (i = 0; i < N; i++) {
        answer += distances[i];
    }
    free(distances);
    free(visited);
    free(previous);
    for (i = 0; i < N; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return answer;
}


int BFS(int** adjacency_matrix) {

}



int main(void) {
    int n;
    int m;
    int i;
    int command;
    int** adjacency_matrix = set_adjacency_matrix(n);
    int x;
    int y;
    int w;
    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d %d %d", &x, &y, &w);
                DSU_node* new_node = malloc(sizeof(DSU_node));
                new_node->value = w;

            case 2:
                scanf("%d", &x);

        }
    }

    printf("%d", get_MST_weight_Prim(N, adjacency_matrix));
    return 0;
}
