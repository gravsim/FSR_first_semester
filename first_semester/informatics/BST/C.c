#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;
    int subtree_size;
    struct Node* left;
    struct Node* right;
} Node;


int node_size(Node* node) {
    /*
        Проверяем, не NULL ли указатель на node, если нет,
        то возвращаем размер его поддерева.
    */
    if (node) {
        return node->subtree_size;
    }
    return 0;
}


void update_size(Node* node) {
    /*
        Обновляем размер поддерева узла node.
    */
    node->subtree_size = 1 + node_size(node->left) + node_size(node->right);
}


int bigger_than(Node* root_p, int value) {
    /*
        Считаем число элементов в дереве, больших value.
        Это и будет порядковый номер узла со значением value.
    */
    int count = 0;
    Node* current = root_p;
    while (current) {
        if (current->value > value) {
            count += 1 + node_size(current->right);
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return count;
}


Node* search_node_by_index(Node* root_p, int index) {
    /*
        Ищем узел с индексом index в дереве current. В нужном узле
        размер правого поддерева должен быть равен порядковому
        номеру элемента в строю. Если индекс больше размера правого поддерева,
        вычитаем из него текущую вершину (одна штука) и размер этого
        правого поддерева и переходим в левую вершину. Иначе переходим в
        правую вершину, повторяем пока индекс и размер правого поддерева
        не сравняются.
    */
    if (!root_p) {
        return NULL;
    }
    Node* current = root_p;
    int right_size = node_size(current->right);
    while (current && right_size != index) {
        if (index > right_size) {
            index -= 1 + right_size;
            current = current->left;
        } else {
            current = current->right;
        }
        right_size = node_size(current->right);
    }
    if (current) {
        return current;
    }
    return NULL;
}


Node* create_node(int value) {
    /*
        Создаем новый узел.
    */
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->subtree_size = 1;
    return new_node;
}


Node* push(Node* root_p, int value) {
    /*
        Рекурсивно добавляем новый лист к дереву, обновляя по пути
        размеры поддеревьев у узлов.
    */
    if (!root_p) {
        return create_node(value);
    }
    if (root_p->value < value) {
        root_p->right = push(root_p->right, value);
    } else if (root_p->value > value) {
        root_p->left = push(root_p->left, value);
    }
    update_size(root_p);
    return root_p;
}


Node* find_min(Node* node) {
    /*
        Ищем узел с минимальным значением в дереве с корнем node.
    */
    if (!node) {
        return NULL;
    }
    while (node->left) {
        node = node->left;
    }
    return node;
}


Node* delete_node(Node* root_p, int value) {
    /*
        Рекурсивно ищем элемент со значением value, начиная с корня,
        чтобы по пути обновлять размеры поддеревьев у узлов. Когда
        находим нужный узел, меняем его значение на минимальное
        значение из его правого поддерева (т.к. оно подходит на его место)
        и удаляем узел с этим минимумом.
    */
    if (!root_p) {
        return NULL;
    }
    if (root_p->value > value) {
        root_p->left = delete_node(root_p->left, value);
    } else if (value > root_p->value) {
        root_p->right = delete_node(root_p->right, value);
    } else {
        // Нашли элемент со значением value, проверяем его детей.
        if (!root_p->right && !root_p->left) {
            // Нет детей
            free(root_p);
            return NULL;
        }
        if (!root_p->right) {
            // Нет только правого ребенка
            Node* tmp = root_p->left;
            free(root_p);
            return tmp;
        }
        if (!root_p->left) {
            // Нет только левого ребенка
            Node* tmp = root_p->right;
            free(root_p);
            return tmp;
        }
        // Есть оба ребенка
        Node* minimal = find_min(root_p->right);
        root_p->value = minimal->value;
        root_p->right = delete_node(root_p->right, minimal->value);
    }
    /*
        После удаления узла, обновляем размеры поддеревьев всех
        узлов, что были выше.
    */
    update_size(root_p);
    return root_p;
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
    int height;
    int index2remove;
    Node* root = NULL;
    int N;
    Node* found;
    scanf("%d", &N);
    int i;
    for (i = 0; i < N; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %d", &height);
                root = push(root, height);
                printf("%d\n", bigger_than(root, height));
                break;
            case 2:
                scanf(" %d", &index2remove);
                found = search_node_by_index(root, index2remove);
                if (found) {
                    root = delete_node(root, found->value);
                }
                break;
            default:
                break;
        }
    }
    free_root(&root);
}
