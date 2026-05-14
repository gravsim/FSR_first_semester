#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 10
#define ALPHABET_SIZE 26


struct TrieNode {
    struct TrieNode** children;
    int end_of_word;
} typedef TrieNode;


int get_index(char symbol) {
    return symbol - 'a';
}


char get_char(int index) {
    return 'a' + index;
}


TrieNode** Trie_search_node(TrieNode** current, char* word, int length) {
    int i = 0;
    int index;
    while (i < length && *current) {
        index = get_index(word[i]);
        current = &(*current)->children[index];
        i++;
    }
    if (i < length) {
        return NULL;
    }
    return current;
}


int Trie_delete_node(TrieNode** node) {
    if (!node || !*node || !(*node)->end_of_word) {
        return 0;
    }
    (*node)->end_of_word = 0;
    return 1;
}


TrieNode* Trie_new_node(void) {
    TrieNode* new_node = malloc(sizeof(TrieNode));
    new_node->children = calloc(ALPHABET_SIZE, sizeof(TrieNode*));
    new_node->end_of_word = 0;
    return new_node;
}


TrieNode* Trie_push(TrieNode* root, char* word, int length) {
    if (root == NULL || word == NULL) {
        root = Trie_new_node();
    }
    TrieNode* current = root;
    int i;
    int index;
    for (i = 0; i < length; i++) {
        index = get_index(word[i]);
        if (!current->children[index]) {
            current->children[index] = Trie_new_node();
        }
        current = current->children[index];
    }
    current->end_of_word = 1;
    return root;
}


int Trie_free_node(TrieNode** node) {
    if (node == NULL || *node == NULL) {
        return 0;
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if ((*node)->children[i]) {
            Trie_free_node(&(*node)->children[i]);
        }
    }
    free((*node)->children);
    free(*node);
    *node = NULL;
    return 1;
}


int read_word(int* length, char* string) {
    if (length == NULL || string == NULL) {
        return 0;
    }
    *length = 0;
    scanf(" %c", string + *length);
    (*length)++;
    while (scanf("%c", string + *length) != EOF && string[*length] != '\n') {
        (*length)++;
    }
    return 1;
}


int main(void) {
    char command;
    TrieNode* root = NULL;
    int length = 0;
    char string[MAX_LENGTH];
    TrieNode** found;
    do {
        scanf("%c", &command);
        switch (command) {
            case '+':
                read_word(&length, string);
                root = Trie_push(root, string, length);
                break;
            case '?':
                read_word(&length, string);
                found = Trie_search_node(&root, string, length);
                if (found && *found && (*found)->end_of_word) {
                    printf("YES\n");
                } else {
                    printf("NO\n");
                }
                break;
            case '-':
                read_word(&length, string);
                found = Trie_search_node(&root, string, length);
                if (found && *found) {
                    Trie_delete_node(found);
                }
                break;
            default:
                break;
        }
    } while (command != '#');
    Trie_free_node(&root);
    return 0;
}
