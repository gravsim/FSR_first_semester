#include <stdio.h>


int main(void){
    int size;
    scanf("%d", &size);
    int max_space;
    if (size <= 3){
        max_space = 1;
    }
    else if(3 < size && size < 10){
        max_space = 2;
    }
    else{
        max_space = 3;
    }
    if (size > 3){
        printf(" ");
    }
    if (size == 10){
        printf(" ");
    }
    for (int i = 1; i <= size; i++){
        for (int j = 1; j <= size; j++){
            int result = i * j;
            int spaces_number;
            if (max_space == 1){
                spaces_number = 1;
            }
            if (max_space == 2){
                if (result < 10){
                    spaces_number = 2;
                }
                else{
                    spaces_number = 1;
                }
            }
            if (max_space == 3){
                if (result < 10){
                    spaces_number = 3;
                }
                else if (10 <= result && result < 100){
                    spaces_number = 2;
                }
                else{
                    spaces_number = 1;
                }
            }
            if (j != 1){
                printf("%*c", spaces_number, ' ');
            }
            printf("%d", result);
        }
        printf("\n");
        if (size > 3 && i < 9){
            printf(" ");
        }
        if (size == 10){
            printf(" ");
        }
        
    }
    return 0;
}
