#include <stdio.h>

void print_number() {
    int number;
    scanf("%d", &number);
    if (number) {
        print_number();
    }
    printf("%d\n", number);
}


int main() {
    print_number();
    return 0;
}
