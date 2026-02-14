#include <stdio.h>
#include <stdlib.h>


typedef struct DSU_node {
    struct DSU_node* parent;
    int sum;
    int rang;
} DSU_node;


DSU_node* make_set(int sum) {
    DSU_node* tmp = malloc(sizeof(DSU_node));
    tmp->sum = sum;
    tmp->parent = tmp;
    tmp->rang = 1;
    return tmp;
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
    if (!node1 || !node2) {
        return NULL;
    }
    node1 = find_set(node1);
    node2 = find_set(node2);
    if (node1->rang < node2->rang) {
        swap_nodes(node1, node2);
    }
    node2->parent = node1;
    if (node1->rang == node2->rang) {
        node1->rang++;
    }
    node1->sum += node2->sum;
    return node1;
}


int main(void) {
    int n;
    int m;
    int i;
    int command;
    int x;
    int y;
    int w;
    scanf("%d %d", &n, &m);
    DSU_node** nodes = calloc(n, sizeof(DSU_node*));
    for (i = 0; i < m; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d %d %d", &x, &y, &w);
                x--;
                y--;
                nodes[i] = make_set(w);
                union_set(nodes[x], nodes[y]);
                break;
            case 2:
                scanf("%d", &x);
                x--;
                printf("\n%d", find_set(nodes[x])->sum);
                break;
        }
    }
    for (i = 0; i < n; i++) {
        free(nodes[i]);
    }
    free(nodes);
    return 0;
}
