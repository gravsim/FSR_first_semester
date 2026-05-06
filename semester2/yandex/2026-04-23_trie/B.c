#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 10000
#define ALPHABET_SIZE 6300


struct TrieNode {
    struct TrieNode** children;
    int end_of_word;
} typedef TrieNode;


TrieNode** Trie_search_node(TrieNode** current, char* word, int length) {
    int i = 0;
    int index = word[i] - 'a';
    while (i < length && *current && (*current)->children[index]) {
        index = word[i] - 'a';
        current = &(*current)->children[index];
        i++;
    }
    if (i < length) {
        return 0;
    }
    return current;
}


int Trie_delete_node(TrieNode** node) {
    (*node)->end_of_word = 0;
    return 1;
}


TrieNode* Trie_new_node() {
    TrieNode* new_node = malloc(sizeof(TrieNode));
    new_node->children = calloc(ALPHABET_SIZE, sizeof(TrieNode*));
    new_node->end_of_word = 0;
    return new_node;
}


TrieNode* Trie_push(TrieNode* root, char* word, int length) {
    if (!root) {
        return Trie_new_node();
    }
    TrieNode* current = root;
    int i;
    int index;
    for (i = 0; i < length; i++) {
        index = word[i] - 'a';
        if (!current->children[index]) {
            current->children[index] = Trie_new_node();
        }
        current = current->children[index];
    }
    current->end_of_word = 1;
    return root;
}


int Trie_free_node(TrieNode** node) {
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if ((*node)->children[i]) {
            Trie_free_node(&(*node)->children[i]);
        }
    }
    free(*node);
    *node = NULL;
    return 1;
}


int Trie_print(TrieNode** node) {
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if ((*node)->children[i]) {
            printf("%c", 'a' + i);
            if ((*node)->end_of_word) {
                printf("\n");
            } else {
                Trie_print(&(*node)->children[i]);
            }
        }
    }
    return 1;
}


int main(void) {
    int command;
    TrieNode* root = NULL;
    int length = 0;
    char string[MAX_LENGTH];
    TrieNode** found;
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                length = 0;
                while (scanf("%c", string + length) != EOF && string[length] != '\n') {
                    length++;
                }
                root = Trie_push(root, string, length);
                printf("1\n");
                break;
            case 2:
                length = 0;
                while (scanf("%c", string + length) != EOF && string[length] != '\n') {
                    length++;
                }
                if (Trie_search_node(&root, string, length)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            case 3:
                length = 0;
                while (scanf("%c", string + length) != EOF && string[length] != '\n') {
                    length++;
                }
                found = Trie_search_node(&root, string, length);
                printf("%d\n", Trie_delete_node(found));
                break;
            case 4:
                Trie_print(&root);
                break;
            default:
                break;
        }
    } while (command != 0);
    Trie_free_node(&root);
    return 0;
}