#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;
    int subtree_size;
    struct Node* left;
    struct Node* right;
} Node;


int node_size(Node* node) {
    if (node) {
        return node->subtree_size;
    }
    return 0;
}


void update_size(Node* node) {
    node->subtree_size = 1 + node_size(node->left) + node_size(node->right);
}


int bigger_than(Node* root_p, int value) {
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


Node** search_node_by_index(Node** root_p, int index) {
    /*
        Ищем узел с индексом index в дереве current.
    */
    Node** current = root_p;
    while (*current) {
        int right_size = node_size((*current)->right);
        if (right_size == index) {
            return current;
        }
        if (index > right_size) {
            index -= 1 + right_size;
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
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
    new_node->subtree_size = 1;
    return new_node;
}


Node* push(Node* root_p, int value) {
    /*
        Добавляем новый лист к дереву.
    */
    if (!root_p) {
        return new_node(value);
    }
    if (root_p->value < value) {
        root_p->right = push(root_p->right, value);
    } else if (root_p->value > value) {
        root_p->left = push(root_p->left, value);
    }
    update_size(root_p);
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
        update_size(*node_pp);
        free(tmp);
        return 1;
    }
    if (!(*node_pp)->left) {
        // Нет только левого ребенка
        *node_pp = (*node_pp)->right;
        update_size(*node_pp);
        free(tmp);
        return 1;
    }
    // Есть оба ребенка
    Node** minimal = find_min(&(*node_pp)->right);
    (*node_pp)->value = (*minimal)->value;
    update_size(*node_pp);
    return delete_node(minimal);
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
    Node** found;
    scanf("%i", &N);
    int i;
    for (i = 0; i < N; i++) {
        scanf("%i", &command);
        switch (command) {
            case 1:
                scanf(" %i", &height);
                root = push(root, height);
                printf("%i\n", bigger_than(root, height));
                break;
            case 2:
                scanf(" %i", &index2remove);
                found = search_node_by_index(&root, index2remove);
                if (found) {
                    delete_node(found);
                }
                break;
            default:
                break;
        }
    }
    free_root(&root);
}
