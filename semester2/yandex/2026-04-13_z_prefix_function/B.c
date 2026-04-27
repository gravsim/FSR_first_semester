#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int max_length = 1000;
    int length = 0;
    char str[max_length];
    while (scanf("%c", str + length) != EOF) {
        length++;
    }
    int* answer = calloc(length, sizeof(int));
    int i = 0;
    int j;
    int k;
    int index;
    for (i = 1; i < length; i++) {
        for (j = length; j >= 0; j--) {
            if (answer[i] == 0) {
                k = 0;
                index = i - j + k + 1;
                while (index >= 0 && index < length && k < j + 1 && str[k] == str[index]) {
                    answer[i]++;
                    k++;
                }
            }
        }
    }
    for (i = 0; i < length; i++) {
        printf("%d ", answer[i]);
    }
    return 0;
}
