#include <stdio.h>
#include <stdlib.h>


int print_way(int v, int i, int n, int* previous) {
    if (i < 0 || i >= n) {
        return 0;
    }
    if (i == v) {
        printf("%d ", i);
        return 1;
    }
    if (previous[i] == -1) {
        return 0;
    }
    if (!print_way(v, previous[i], n, previous)) {
        return 0;
    }
    printf("%d ", i);
    return 1;
}


int main(void) {
    int v;
    int n = 10000;
    int command;
    int i;
    int* previous = calloc(n, sizeof(int));
    scanf("%d", &command);
    int to;
    while (command != 3) {
        switch (command) {
            case 1:
                scanf("%d %d", &v, &n);
                for (i = 0; i < n; i++) {
                    scanf("%d", previous + i);
                }
                break;
            case 2:
                scanf("%d", &to);
                if (previous[to] == -1 || !print_way(v, to, n, previous)) {
                    printf("-1");
                }
                break;
            default:
                break;
        }
        scanf("%d", &command);
    }
    return 0;
}