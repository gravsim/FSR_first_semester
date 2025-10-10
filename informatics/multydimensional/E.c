#include <stdio.h>


int main() {
    char array[8][8];
    int attacked[8][8] = {0, 0};
    int i, j, k;
    int x, y;
    int number;
    char character;
    int answer = 64;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            scanf("%c", &character);
            array[i][j] = character;
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            switch (array[i][j]) {
                case '*':
                    break;
                case 'R':
                    for (k = 0; k < 8; k++) {
                        attacked[k][j] = 1;







                        
                        attacked[i][k] = 1;
                        // сука че за хуйня
                    }
                    break;

            }
        }
    }
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            answer -= attacked[i][j];
            printf("%d ", answer);
        }
    }
    printf("%d", answer);
    return 0;
}
