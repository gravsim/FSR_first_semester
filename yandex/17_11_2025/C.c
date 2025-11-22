#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;


int search(Node* root_p, int value) {
    int biggest = INT_MIN;
    if (!root_p) {
        return biggest;
    }
    if (root_p->value == value) {
        return value;
    }
    Node* current = root_p;
    while (current) {
        if (current->value > biggest && current->value < value) {
            biggest = current->value;
        }
        if (current->value < value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return biggest;
}


Node* find_leaf(Node* root_p, int value) {
    Node* current = root_p;
    while (current) {
        if (current->value > value) {
            if (!current->right) {
                return current;
            }
            current = current->right;
        } else {
            if (!current->left) {
                return current;
            }
            current = current->left;
        }
    }
    return NULL;
}



int push(Node** root_pp, int value) {
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    if (!*root_pp) {
        *root_pp = new_node;
        return 1;
    }
    Node* leaf = find_leaf(*root_pp, value);
    if (!leaf) {
        return 0;
    }
    if (leaf->value > value) {
        leaf->right = new_node;
    } else {
        leaf->left = new_node;
    }
    return 1;
}


int delete_leaf(Node** leaf_pp) {
    if ((*leaf_pp)->left) {
        delete_leaf(&(*leaf_pp)->left);
    }
    if ((*leaf_pp)->right) {
        delete_leaf(&(*leaf_pp)->right);
    }
    free(*leaf_pp);
    *leaf_pp = NULL;
    return 1;
}


int delete_root(Node** root_pp) {
    if (!root_pp || !*root_pp) {
        return 1;
    }
    if ((*root_pp)->left) {
        delete_leaf(&(*root_pp)->left);
    }
    if ((*root_pp)->right) {
        delete_leaf(&(*root_pp)->right);
    }
    free(*root_pp);
    *root_pp = NULL;
    return 1;
}


int main(void) {
    int command;
    int value;
    Node* root = NULL;
    do {
        scanf("%i", &command);
        switch (command) {
            case 1:
                scanf(" %i", &value);
                push(&root, value);
                break;
            case 2:
                scanf(" %i", &value);
                int biggest = search(root, value);
                printf("Biggest bitch: %i; ", biggest);
                if (biggest == INT_MIN) {
                    printf("The entered value is not stored in the tree\n");
                } else if (value == biggest) {
                    printf("The entered value is minimal\n");
                } else {
                    printf("%i\n", biggest);
                }
                break;
            case 3:
                delete_root(&root);
                break;
            default:
                break;
        }
        printf("STEP!\n");
    } while (command != 0);
    delete_root(&root);
    return 0;
}
