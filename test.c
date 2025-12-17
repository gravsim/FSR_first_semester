#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int equal_of_points(double x1, double y1, double x2, double y2){
    return fabs(x1 - x2) < 1e-8 && fabs(y1 - y2) < 1e-8;
}

int line_crossing(double a1, double b1, double c1, double a2, double b2, double c2, double *x, double * y){
    if (fabs(a1 * b2 - a2 * b1) < 1e-8){
        return 0;
    }
    *x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
    *y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
    return 1;
}

int check_rectangle(double x, double y, double x_rectangle, double y_rectangle){
    if (x >= (-1) * (1e-8) && x <= x_rectangle + 1e-8 &&  y >= (-1) * (1e-8) && y <= y_rectangle + 1e-8){
        return 1;
    }
    return 0;
}

int check_in_triangle(double p1, double p2, double x1, double y1, double x2, double y2, double x3, double y3){
    double s1 = (p1 - x2) * (y1 - y2) - (x1 - x2) * (p2 - y2);
    double s2 = (p1 - x3) * (y2 - y3) - (x2 - x3) * (p2 - y3);
    double s3 = (p1 - x1) * (y3 - y1) - (x3 - x1) * (p2 - y1);


    if (fabs(s1) < 1e-8 || fabs(s2) < 1e-8 || fabs(s3) < 1e-8){
        return 0;
    }
    int signum1 = -1, signum2 = -1, signum3 = -1;
    if (s1 > 0){
        signum1 = 1;
    }
    if (s2 > 0){
        signum2 = 1;
    }
    if (s3 > 0){
        signum3 = 1;
    }
    return (signum1 == signum2) && (signum2 == signum3);
}

int checking_edge(int a, int b, int **neighbours, int * neighbours_counter){
    if(a == b){
        return 0;
    }
    for (int i = 0; i < neighbours_counter[a]; i++){
        if (neighbours[a][i] == b){
            return 1;
        }
    }
    return 0;
}


int main(void){
    double x_rectangle, y_rectangle;
    scanf("%lf %lf", &x_rectangle, &y_rectangle);
    int n;
    scanf("%d", &n);
    double **arr = calloc(n + 4 , sizeof(double *));
    for (int i = 0; i < n + 4; i++){
        arr[i] = calloc(3, sizeof(double));
    }
    //вносим линии прямоугольника
    arr[0][0] = 1.0;
    arr[0][1] = 0.0;
    arr[0][2] = 0.0;
    arr[1][0] = 0.0;
    arr[1][1] = 1.0;
    arr[1][2] = 0.0;
    arr[2][0] = 1.0;
    arr[2][1] = 0.0;
    arr[2][2] = (-1) * x_rectangle;
    arr[3][0] = 0.0;
    arr[3][1] = 1.0;
    arr[3][2] = (-1) * y_rectangle;
    for (int i = 4; i < n + 4; i++){
        scanf("%lf %lf %lf", &arr[i][0], &arr[i][1], &arr[i][2]);
    }
    double * arr_of_x = calloc((n + 4) * (n + 3) / 2, sizeof(double));
    double * arr_of_y = calloc((n + 4) * (n + 3) / 2, sizeof(double));
    int point_counter = 0;
    n = n + 4;//есть еще прямоугольник сам, его тоже считаем
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            double x_tmp, y_tmp;
            if (line_crossing(arr[i][0], arr[i][1], arr[i][2],
            arr[j][0], arr[j][1], arr[j][2], &x_tmp, &y_tmp)){
                if (check_rectangle(x_tmp, y_tmp, x_rectangle, y_rectangle)){
                    int flag = 0;
                    for (int k = 0; k < point_counter&&(!flag); k++){
                        if (equal_of_points(arr_of_x[k], arr_of_y[k], x_tmp, y_tmp)){
                            flag = 1;
                        }
                    }
                    if (!flag){
                        arr_of_x[point_counter] = x_tmp;
                        arr_of_y[point_counter] = y_tmp;
                        point_counter++;
                    }
                }
            }
        }
    }
    int ** neighbours = calloc(point_counter, sizeof(int*));
    int * neighbour_counter = calloc(point_counter, sizeof(int));

    int * tmp_indeces = calloc(point_counter, sizeof(int));
    double * tmp_values = calloc(point_counter, sizeof(double));


    for (int i = 0; i < n; i++){
        int counter_on_line = 0;
        for (int j = 0; j < point_counter; j++){
            double value = arr[i][0] * arr_of_x[j] + arr[i][1] * arr_of_y[j] + arr[i][2];
            if (fabs(value) < 1e-8){
                tmp_indeces[counter_on_line] = j;
                //проверем вертикальность и горизонтальность - чтобы понимать, по какому параметру сортируем
                if (fabs(arr[i][1]) < 1e-8){
                    tmp_values[counter_on_line] = arr_of_y[j];
                }
                else{
                    tmp_values[counter_on_line] = arr_of_x[j];
                }
                counter_on_line++;
            }
        }
        if (counter_on_line > 1){
            //пузырек так как двумя массивами оперируем
            for (int j = 0; j < counter_on_line - 1; j++){
                for (int k = 0; k < counter_on_line - j - 1; k++){
                    if(tmp_values[k] > tmp_values[k + 1]){
                        double tmp_value = tmp_values[k];
                        tmp_values[k] = tmp_values[k + 1];
                        tmp_values[k + 1] = tmp_value;

                        int tmp_index = tmp_indeces[k];
                        tmp_indeces[k] = tmp_indeces[k + 1];
                        tmp_indeces[k + 1] = tmp_index;

                        //меняем индексы и значения местами
                    }
                }
            }
            for (int j = 0; j < counter_on_line - 1; j++){
                neighbour_counter[tmp_indeces[j]]++;
                neighbour_counter[tmp_indeces[j + 1]]++;
            }
        }
    }

    for (int i = 0; i < point_counter; i++){
        neighbours[i] = calloc(neighbour_counter[i], sizeof(int));
        neighbour_counter[i] = 0;
    }
    //вторым проход заполняем соседей
    for (int i = 0; i < n; i++){
        int counter_on_line = 0;
        for (int j = 0; j < point_counter; j++){
            double value = arr[i][0] * arr_of_x[j] + arr[i][1] * arr_of_y[j] + arr[i][2];
            if (fabs(value) < 1e-8){
                tmp_indeces[counter_on_line] = j;
                if (fabs(arr[i][1]) < 1e-8){
                    tmp_values[counter_on_line] = arr_of_y[j];
                }
                else{
                    tmp_values[counter_on_line] = arr_of_x[j];
                }
                counter_on_line++;
            }
        }

        if (counter_on_line > 1){
            for (int j = 0; j < counter_on_line - 1; j++){
                for (int k = 0; k < counter_on_line - j - 1; k++){
                    if(tmp_values[k] > tmp_values[k + 1]){
                        double tmp_value = tmp_values[k];
                        tmp_values[k] = tmp_values[k + 1];
                        tmp_values[k + 1] = tmp_value;

                        int tmp_index = tmp_indeces[k];
                        tmp_indeces[k] = tmp_indeces[k + 1];
                        tmp_indeces[k + 1] = tmp_index;
                    }
                }
            }
            for (int j = 0; j < counter_on_line - 1; j++){
                neighbours[tmp_indeces[j]][neighbour_counter[tmp_indeces[j]]] = tmp_indeces[j + 1];
                neighbour_counter[tmp_indeces[j]]++;
                neighbours[tmp_indeces[j + 1]][neighbour_counter[tmp_indeces[j + 1]]] = tmp_indeces[j];
                neighbour_counter[tmp_indeces[j + 1]]++;
            }
        }
    }
    free(tmp_indeces);
    free(tmp_values);


    int counter = 0;
    for (int i = 0; i < point_counter; i++){
        for (int j = 0; j < neighbour_counter[i]; j++){
            int vertex_j = neighbours[i][j];
            if (vertex_j > i){
                for (int k = 0; k < neighbour_counter[i]; k++){
                    int vertex_k = neighbours[i][k];
                    if (vertex_k > vertex_j){
                        if (checking_edge(vertex_j, vertex_k, neighbours, neighbour_counter)){
                            double square = fabs((arr_of_x[vertex_j] - arr_of_x[i]) * (arr_of_y[vertex_k] - arr_of_y[i]) -
                            (arr_of_x[vertex_k] - arr_of_x[i]) * (arr_of_y[vertex_j] - arr_of_y[i])) / 2;
                            if (square > 1e-8){
                                int flag_of_inside_triangle = 0;
                                for (int o = 0; o < point_counter && (!flag_of_inside_triangle); o++){
                                    if (o != i && o != vertex_j && o != vertex_k){
                                        if (check_in_triangle(arr_of_x[o], arr_of_y[o],
                                        arr_of_x[i], arr_of_y[i], arr_of_x[vertex_j], arr_of_y[vertex_j],
                                        arr_of_x[vertex_k], arr_of_y[vertex_k])){
                                            flag_of_inside_triangle = 1;
                                        }
                                    }
                                }
                                if (!flag_of_inside_triangle){
                                    //проверка, что не на одной прямой
                                    counter++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("%d", counter);
    for (int i = 0; i < point_counter; i++){
        free(neighbours[i]);
    }
    for (int i = 0; i < n; i++){
        free(arr[i]);
    }
    free(arr_of_x);
    free(neighbour_counter);
    free(arr_of_y);
    free(arr);
    free(neighbours);
    return 0;
}
