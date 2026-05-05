#include <stdio.h>


int substring_equal(char* string1, char* string2, int indentation, int len) {
    if (string1 == NULL || string2 == NULL) {
        return -1;
    }
    int i = 0;
    while (i < len && string1[i] == string2[(indentation + i) % len] ) {
        i++;
    }
    if (i == len) {
        return 1;
    }
    return 0;
}


int main(void) {
    int max_length = 10000;
    int length = 0;

    char str1[max_length];
    char str2[max_length];
    int i;
    int j;
    while (scanf("%c", str1 + length) != EOF && str1[length] != '\n') {
        length++;
    }
    for (i = 0; i < length; i++) {
        scanf("%c", str2 + i);
    }
    i = 0;
    while (i < length && !substring_equal(str1, str2, i, length)) {
        i++;
    }
    if (i < length) {
        printf("%d", i);
    } else {
        printf("-1");
    }
    return 0;
}
