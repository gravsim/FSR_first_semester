#include <stdio.h>


void separate(int N) {
    if (N > 1) {
        separate(N - 1);
        printf("%d 1\n", N - 1);
    }
    return 
}


int main() {
    int N;
    scanf("%d", &N);
    separate(N);
    return 0;
}
