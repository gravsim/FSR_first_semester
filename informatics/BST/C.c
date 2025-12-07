#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;


Node** search_node(Node** current, int* sum, int index) {
    /*
        Ищем узел с индексом index в дереве current.
    */
    printf("FINDING");
    if (!current || !*current) {
        return NULL;
    }
    if ((*current)->left) {
        // Ищем в левом поддереве.
        Node** left_result = search_node(&(*current)->left, sum, index);
        if (left_result) {
            return left_result;
        }
    }
    if (*sum == index) {
        // Если индекс элемента совпал с нужным, возвращаем его.
        return current;
    }
    (*sum)++;
    if ((*current)->right) {
        // Ищем в правом поддереве.
        return search_node(&(*current)->right, sum, index);
    }
    // Ничего не нашли.
    return NULL;
}


Node* new_node(int value) {
    /*
        Создаем новый узел.
    */
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


Node* push(Node* root_p, int value) {
    /*
        Добавляем новый лист к дереву.
    */
    if (!root_p) {
        return new_node(value);
    }
    if (value == root_p->value) {
        return root_p;
    }
    if (root_p->value < value) {
        root_p->right = push(root_p->right, value);
    } else {
        root_p->left = push(root_p->left, value);
    }
    return root_p;
}


Node** find_min(Node** node) {
    /*
        Ищем узел с минимальным значением в дереве с корнем node.
    */
    if (!*node) {
        return NULL;
    }
    while ((*node)->left) {
        node = &(*node)->left;
    }
    return node;
}


int delete_node(Node** node_pp) {
    if (!node_pp || !*node_pp) {
        return 0;
    }
    Node* tmp = *node_pp;
    if (!(*node_pp)->right && !(*node_pp)->left) {
        // Нет детей
        free(tmp);
        *node_pp = NULL;
        return 1;
    }
    if (!(*node_pp)->right) {
        // Нет только правого ребенка
        *node_pp = (*node_pp)->left;
        free(tmp);
        return 1;
    }
    if (!(*node_pp)->left) {
        // Нет только левого ребенка
        *node_pp = (*node_pp)->right;
        free(tmp);
        return 1;
    }
    // Есть оба ребенка
    Node** descendant = find_min(&(*node_pp)->right);
    (*node_pp)->value = (*descendant)->value;
    return delete_node(descendant);
}



int free_node(Node** leaf_pp) {
    /*
        Освобождаем память узлов дерева. Если есть потомки,
        запускаем освобождение для них.
        Не проверяем leaf_pp == NULL, т.к. это было сделано
        до старта рекурсии для данного узла.
    */
    if ((*leaf_pp)->left) {
        free_node(&(*leaf_pp)->left);
    }
    if ((*leaf_pp)->right) {
        free_node(&(*leaf_pp)->right);
    }
    free(*leaf_pp);
    *leaf_pp = NULL;
    return 1;
}


int free_root(Node** root_pp) {
    /*
        Освобождаем память корня дерева. Если есть
        потомки, запускаем освобождение для них.
    */
    if (!root_pp || !*root_pp) {
        return -1;
    }
    if ((*root_pp)->left) {
        free_node(&(*root_pp)->left);
    }
    if ((*root_pp)->right) {
        free_node(&(*root_pp)->right);
    }
    free(*root_pp);
    *root_pp = NULL;
    return 1;
}


int main(void) {
    int command;
    int value;
    Node* root = NULL;
    int N;
    int sum;
    Node** found;
    scanf("%i", &N);
    int i;
    for (i = 0; i < N; i++) {
        scanf("%i", &command);
        switch (command) {
            case 1:
                scanf(" %i", &value);
                root = push(root, value);
                sum = 0;
                search_node(&root, &sum, value);
                printf("%i\n", sum);
                break;
            case 2:
                scanf(" %i", &value);
                sum = 0;
                found = search_node(&root, &sum, value);
                delete_node(found);
                break;
            default:
                break;
        }
    }
    free_root(&root);
}
