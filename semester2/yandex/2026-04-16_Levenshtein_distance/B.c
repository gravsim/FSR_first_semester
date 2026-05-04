#include <stdio.h>
#include <stdlib.h>


int z_function(char* str, int* answer, int length) {
    if (str == NULL || answer == NULL) {
        return -1;
    }
    int i = 0;
    int j;
    for (i = 1; i < length; i++) {
        j = 0;
        while (i + j < length && str[j] == str[i + j]) {
            answer[i]++;
            j++;
        }
    }
    return 1;
}


int main(void) {
    int pattern_len;
    int text_len;
    scanf("%d %d", &pattern_len, &text_len);
    int len = pattern_len + text_len + 2;
    char* text = calloc(len, sizeof(char));
    int i;
    scanf("%c", text);
    for (i = 0; i < len; i++) {
        scanf("%c", text + i);
    }
    text[pattern_len] = '`';
    int* answer = calloc(len, sizeof(int));
    z_function(text, answer, len);
    i = pattern_len;
    while (answer[i] != pattern_len) {
        i++;
    }
    printf("%d ", i - pattern_len - 1);
    free(text);
    free(answer);
    return 0;
}
