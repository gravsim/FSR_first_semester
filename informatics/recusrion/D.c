#include <stdio.h>
#include <stdlib.h>



int char2int(char number) {
    return number - '0';
}


int is_number(char number) {
    return (number >= '0' && number <= '9');
}


int extract_multiplier(int* i, char* array) {
    int multiplier = 0;
    int sign = 1;
    if (array[*i] == '-') {
        sign = -1;
    }
    (*i)++;
    if (array[*i] == 'x') {
        multiplier = 1;
        return sign * multiplier;
    }
    while (is_number(array[*i])) {
        multiplier *= 10;
        multiplier += char2int(array[*i]);
        (*i)++;
    }
    return sign * multiplier;
}


int extract_power(int* i, char* array) {
    int power = 0;
    if (array[*i] == 'x') {
        (*i)++;
        if (array[*i] == '^') {
            (*i)++;
            while (is_number(array[*i])) {
                power *= 10;
                power += char2int(array[*i]);
                (*i)++;
            }
        } else {
            power = 1;
        }
    } else if (array[*i] == '\0') {
        power = 0;
    }
    return power;
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
    int power = 1;
    int multiplier;
    while (polynomial[i] != '\0' && power != 0) {
        multiplier = extract_multiplier(&i, polynomial);
        power = extract_power(&i, polynomial);
        // printf("\nMultiplier: %d", multiplier);
        // printf(", power: %d ", power);
        multipliers[power] = multiplier;
    }
    // printf("\nArray readed.\n\n");
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
    for (i = 10; i >= 0; i--) {
        if (polynomial[i] != 0) {
            if (counter > 0 && polynomial[i] > 0) {
                printf("+");
            }
            if (polynomial[i] != 1 || i == 0) {
                if (polynomial[i] == -1) {
                    printf("-");
                } else {
                    printf("%d", polynomial[i]);
                }
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
