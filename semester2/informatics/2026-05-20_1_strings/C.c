#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 100000
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


int print_string(char* string, int length) {
    if (string == NULL) {
        return 0;
    }
    int i;
    for (i = 0; i < length; i++) {
        printf("%c", string[i]);
    }
    printf("\n");
    return 1;
}


int Trie_check(
    int print,
    TrieNode* node,
    char* sample,
    int depth,
    int max_prefix,
    int* total
    ) {
    if (node == NULL || sample == NULL) {
        return 0;
    }
    int i;
    if (depth <= max_prefix) {
        if (node->end_of_word) {
            (*total)++;
            if (print) {
                print_string(sample, depth);
            }
        }
        for (i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                sample[depth] = get_char(i);
                Trie_check(
                    print,
                    node->children[i],
                    sample,
                    depth + 1,
                    max_prefix,
                    total
                    );
            }
        }
        return 0;
    }
    i = 0;
    int result = 0;
    while (i < ALPHABET_SIZE && !result) {
        if (node->children[i]) {
            sample[depth] = get_char(i);
            result = Trie_check(print,
                node->children[i],
                sample,
                depth + 1,
                max_prefix,
                total
                );
        }
        i++;
    }
    if (!result && node->end_of_word) {
        (*total)++;
        if (print) {
            print_string(sample, depth);
        }
        return 1;
    }
    return result;
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
    long amount;
    int max_prefix;
    scanf("%ld %d", &amount, &max_prefix);
    long i;
    TrieNode* root = NULL;
    int length = 0;
    int total = 0;
    char string[MAX_LENGTH];
    char* sample = calloc(MAX_LENGTH, sizeof(char));
    for (i = 0; i < amount; i++) {
        read_word(&length, string);
        root = Trie_push(root, string, length);
    }
    Trie_check(0, root, sample, 0, max_prefix, &total);
    printf("%d\n", total);
    Trie_check(1, root, sample, 0, max_prefix, &total);
    free(sample);
    Trie_free_node(&root);
    return 0;
}
