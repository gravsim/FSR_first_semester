#include <stdio.h>


int main(void) {
    double e_input = 0.0;
    double min_e = 2.718281;
    double max_e = 2.718282;
    scanf("%lf", &e_input);
    if (min_e <= e_input && e_input < max_e) {
        printf("YES");
    }
    else {
        printf("NO");
    }
    return 0;
}
