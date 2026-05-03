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
    int max_length = 1000;
    int length = 0;
    char str[max_length];
    int i;
    while (scanf("%c", str + length) != EOF && str[length] != '\n') {
        length++;
    }
    int* answer = calloc(length, sizeof(int));
    z_function(str, answer, length);
    for (i = 0; i < length; i++) {
        printf("%d ", answer[i]);
    }
    free(answer);
    return 0;
}
