#include <stdio.h>


void swap(char* a, char* b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}


int invert(char* letter) {
    /*
        Меняем направление движения на противоположное.
    */
    if (!letter) {
        return -1;
    }
    switch (*letter) {
        case 'E':
            *letter = 'W';
            break;
        case 'W':
            *letter = 'E';
            break;
        case 'N':
            *letter = 'S';
            break;
        case 'S':
            *letter = 'N';
            break;
        default:
            break;
    }
    return 1;
}


int angle(int positions[][2], int pos_len, int i, int j) {
    /*
        Проверяем, что в данной точке действительно самопересечение,
        а не самокасание. Это будет самопересечение, если данная точка находится
        в середине отрезка двух соседних точек по x и по y.
    */
    if (i > 0 && i < pos_len - 1 && j > 0 && j < pos_len - 1) {
        if (positions[j + 1][0] + positions[j - 1][0] == 2 * positions[j][0] &&
            positions[j + 1][1] + positions[j - 1][1] == 2 * positions[j][1] &&
            positions[i + 1][0] + positions[i - 1][0] == 2 * positions[i][0] &&
            positions[i + 1][1] + positions[i - 1][1] == 2 * positions[i][1]) {
            return 1;
        }
    }
    return 0;
}


int read_sequence(char sequence[], int* sequence_len) {
    /*
        Читаем последовательность, игнорируя пробелы и прочие
        знаки между символами.
    */
    if (!sequence_len) {
        return -1;
    }
    char raw_sequence[201];
    fgets(raw_sequence, sizeof(raw_sequence), stdin);
    int i = 0;
    while (raw_sequence[i]) {
        if (raw_sequence[i] == 'W' || raw_sequence[i] == 'S' || raw_sequence[i] == 'E' || raw_sequence[i] == 'N') {
            sequence[(*sequence_len)++] = raw_sequence[i];
        }
        i++;
    }
    sequence[*sequence_len] = '\0';
    return 1;
}


int update_positions(int positions[][2], int* pos_len, int sequence_len, char* sequence) {
    /*
        Обновляем массив с координатами по заданной последовательности
        сдвигов.
    */
    if (!positions || !sequence) {
        return -1;
    }
    for (*pos_len = 1; *pos_len <= sequence_len; (*pos_len)++) {
        switch (sequence[*pos_len - 1]) {
            case 'E':
                positions[*pos_len][0] = positions[*pos_len - 1][0] + 1;
                positions[*pos_len][1] = positions[*pos_len - 1][1];
                break;
            case 'W':
                positions[*pos_len][0] = positions[*pos_len - 1][0] - 1;
                positions[*pos_len][1] = positions[*pos_len - 1][1];
                break;
            case 'N':
                positions[*pos_len][0] = positions[*pos_len - 1][0];
                positions[*pos_len][1] = positions[*pos_len - 1][1] + 1;
                break;
            case 'S':
                positions[*pos_len][0] = positions[*pos_len - 1][0];
                positions[*pos_len][1] = positions[*pos_len - 1][1] - 1;
                break;
            default:
                break;
        }
    }
    return 1;
}


int main(void) {
    /*
        Из последовательности сдвигов робота создаем массив с
        последовательностью позиций робота после каждого сдвига
        ((x0, y0), (x1, y1), (x2, y2), ...). Начальная точка всегда (0, 0).
        Ищем в массиве совпадающие координаты, в них либо самопересечение,
        либо самокасание. В функции angle определяем самопересечения. Если
        самопересечение, то инвертируем полученный цикл, чтобы получилось
        самокасание. Обновляем координаты после инверсии и продолжаем
        проверку координат, пока не дойдем до конца. Получим новую
        последовательность без самопересечений.
    */
    char sequence[201];
    int positions[201][2] = {{0, 0}};
    int sequence_len = 0;
    int pos_len;
    int i, j, k;
    read_sequence(sequence, &sequence_len);
    update_positions(positions, &pos_len, sequence_len, sequence);
    for (i = 0; i < pos_len; i++) {
        for (j = i + 1; j < pos_len; j++) {
            if (positions[i][0] == positions[j][0] && positions[i][1] == positions[j][1]) {
                if (angle(positions, pos_len, i, j)) {
                    for (k = i; k < j; k++) {
                        // Инвертируем все шаги в цикле.
                        invert(&sequence[k]);
                    }
                    for (k = i; k < (j + i) / 2; k++) {
                        // Симметрично отражаем цикл, относительно  его середины.
                        swap(&sequence[k], &sequence[j - (k - i) - 1]);
                    }
                    // Обновляем координаты точек в маршруте.
                    update_positions(positions, &pos_len, sequence_len, sequence);
                }
            }
        }
    }
    printf("%s", sequence);
    return 0;
}
