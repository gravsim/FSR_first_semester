#include <stdio.h>
#include <stdlib.h>


void put(long* spase, long value) {
    *spase = value;
}


void my_scanf(long* variable) {
    scanf("%ld", variable);
}


void my_printf(long* variable) {
    printf("%ld", *variable);
}


void print_zero(void) {
    printf("0");
}


void increment(long* variable) {
    (*variable)++;
}


int is_equal(long* value1, long* value2) {
    return *value1 == *value2;
}


int is_smaller(long* value1, long value2) {
    return *value1 < value2;
}


void cycle1(long* iterable, long* len, long* array) {
    for (put(iterable, 0); is_smaller(iterable, *len); increment(iterable)) {
        my_scanf(&array[*iterable]);
    }
}


void cycle3(long* iterable1, long* iterable2, long* len, long* array, long* empty) {
    for (put(iterable2, (*iterable1) + 1); is_smaller(iterable2, *len); increment(iterable2)) {
        if (is_equal(&array[*iterable1], &array[*iterable2])) {
            put(&array[*iterable2], *empty);
        }
    }
}


void cycle2(long* iterable1, long* iterable2, long* len, long* array, long* empty, long* unique) {
    for (put(iterable1, 0); is_smaller(iterable1, (*len) - 1); increment(iterable1)) {
        if (!is_equal(&array[*iterable1], empty)) {
            increment(unique);
            cycle3(iterable1, iterable2, len, array, empty);
        }
    }
}


int main(void) {
    long N;
    my_scanf(&N);
    long* array = (long*)calloc(N, sizeof(long));
    long unique;
    put(&unique, 0);
    long i, j;
    long empty;
    put(&empty, 2147483645);
    cycle1(&i, &N, array);
    cycle2(&i, &j, &N, array, &empty, &unique);
    if (!is_equal(&array[i], &empty)) {
        increment(&unique);
    }
    my_printf(&unique);
    free(array);
    return 0;
}