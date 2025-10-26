#include <stdio.h>
#include <stdlib.h>



int char2int(char number) {
    return number - '0';
}


int is_number(char number) {
    return (number >= '0' && number <= '9');
}


int extract_number(int* i, char* array) {
    int number = 0;
    int sign = 1;
    if (array[*i] == 'x') {
        return 1;
    }
    if (array[*i] == '-') {
        printf("BEBAR ");
        number = 1;
        sign = -1;

    }
    while (is_number(array[*i])) {
        number *= 10;
        number += char2int(array[*i]);
        (*i)++;
    }
    printf("Coeff: %d\n", sign * number);
    return sign * number;
}


void print_array(int N, int* array) {
    int i;
    printf("\nArray: ");
    for (i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void read_polynomial(char* polynomial, int* multipliers) {
    int i = 0;
    int index;
    int multiplier;
    while (polynomial[i] != '\0') {
        if (polynomial[i - 1] == '+' || i == 0) {
            multiplier = extract_number(&i, polynomial);
            i += 1;
            if (polynomial[i] == '^') {
                i++;
                index = extract_number(&i, polynomial);
            } else if (polynomial[i] == '+' || polynomial[i - 1] == 'x') {
                index = 1;
            } else if (polynomial[i] == '\0') {
                index = 0;
            }
            // printf("index: %d, value = %c ", index, polynomial[i]);
            multipliers[index] = multiplier;
        } else {
            i++;
        }
    }
}


void get_multiplication(int* result, int* multipliers1, int* multipliers2) {
    int i, j, k;
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 11; j++) {
            for (k = 0; k < 11; k++) {
                if (j + k == i) {
                    result[i] += multipliers1[j] * multipliers2[k];
                }
            }
        }
    }
}


void print_polynomial(int* polynomial) {
    int i;
    int counter = 0;
    for (i = 10; i >=0; i--) {
        if (polynomial[i] > 0) {
            if (counter > 0) {
                printf("+");
            }
            if (polynomial[i] != 1) {
                printf("%d", polynomial[i]);
            }
            if (i > 1) {
                printf("x^%d", i);
            } else if (i == 1) {
                printf("x");
            }
            counter++;
        }
    }
}



int main() {
    char polynomial1[100];
    char polynomial2[100];
    scanf("%s", polynomial1);
    scanf("%s", polynomial2);
    int multipliers1[11] = {0};
    int multipliers2[11] = {0};
    read_polynomial(polynomial1, multipliers1);
    read_polynomial(polynomial2, multipliers2);
    print_array(11, multipliers1);
    print_array(11, multipliers2);
    int result[11] = {0};
    get_multiplication(result, multipliers1, multipliers2);
    // print_array(11, result);
    print_polynomial(result);
    return 0;
}
