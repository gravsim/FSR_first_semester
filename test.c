#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n = 0;
    scanf("%d", &n);
    char ** arr = calloc (n, sizeof(char*));
    for (int i = 0; i < n; i++){
        arr[i] = calloc(n, sizeof(char));
    }
    char c = 'c';
    scanf("%c", &c);
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            scanf("%c", &c);
            if (c == 'R' || c == 'B'){
                arr[i][j] = c;
            }
        }
        scanf("%c", &c);
    }

    int quality = (n / 64) + 1;
    unsigned long long ** arr_red = calloc(n ,sizeof(unsigned long long *));
    unsigned long long ** arr_blue = calloc(n ,sizeof(unsigned long long *));
    for (int i = 0; i < n; i++){
        arr_red[i] = calloc(quality, sizeof(unsigned long long));
        arr_blue[i] = calloc(quality, sizeof(unsigned long long));
    }

    for (int i = n - 1; i >= 0; i--){
        for (int j = i + 1; j < n; j++){
            unsigned long long tmp = 1ULL << (j % 64);
            if (arr[i][j] == 'R'){
                arr_red[i][j / 64] |= tmp;
                for (int k = 0; k < j / 64; k++){
                    arr_red[i][k] |=arr_red[j][k];
                }
            }
            else{
                if (arr[i][j] == 'B'){
                    arr_blue[i][j / 64] |= tmp;
                    for (int k = 0; k < j / 64; k++){
                        arr_blue[i][k] |=arr_blue[j][k];
                    }
                }
            }
        }
    }

    int flag = 0;
    for (int i = 0; i < n  && (!flag); i++){
        for (int j = i + 1; j < n && (!flag); j++){
            unsigned long long tmp = 1ULL << (j % 64);
            if ((arr_red[i][j / 64] & tmp) && (arr_blue[i][j / 64] & tmp)){
                flag = 1;
            }
        }
    }

    if (!flag){
        printf("NO");
    }
    else{
        printf("YES");
    }
    for (int i = 0; i < n; i++){
        free(arr_blue[i]);
        free(arr_red[i]);
        free(arr[i]);
    }
    free(arr_blue);
    free(arr_red);
    free(arr);
    return 0;
}
