#include <stdio.h>

int main(void){
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);

    if ((a + b) % 2 == 0){
        printf("YES");
    }
    else{
        printf("NO");
    }
    return 0;
}