#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Queue {
    int front;
    int back;
    int capacity;
    int* values;
} Queue;


int norm_index(Queue* queue, int index) {
    return (index % queue->capacity + queue->capacity) % queue->capacity;
}


int is_full(Queue* queue) {
    if (!queue) {
        return 0;
    }
    return queue->back - queue->front == queue->capacity;
}


void expand(Queue* queue) {
    if (!queue) {
        return;
    }
    queue->front = norm_index(queue, queue->front);
    queue->back = norm_index(queue, queue->back);
    int old_capacity = queue->capacity;
    queue->capacity *= 2;
    int* tmp_values = realloc(queue->values, queue->capacity * sizeof(int));
    if (!tmp_values) {
        return;
    }
    queue->values = tmp_values;
    int i;
    if (queue->front >= queue->back) {
        for (i = 0; i < queue->back; i++) {
            queue->values[i + old_capacity] = queue->values[i];
        }
        queue->back += old_capacity;
    }
}


int push(Queue* queue, int* value) {
    if (!queue || !value) {
        return -1;
    }
    if (is_full(queue)) {
        expand(queue);
    }
    queue->values[norm_index(queue, queue->back)] = *value;
    queue->back++;
    return 0;
}


int pop(Queue* queue, int* value) {
    if (!queue || !value) {
        return -1;
    }
    *value = queue->values[norm_index(queue, queue->front)];
    queue->front++;
    return 0;
}


Queue* init_queue(int N) {
    Queue* queue = malloc(sizeof(Queue));
    queue->front = 0;
    queue->back = 0;
    queue->capacity = N + 1;
    queue->values = (int*)calloc(queue->capacity, sizeof(int));
    return queue;
}


void array_max(int* array, int size, int* max, int* max_index) {
    /*
     Ищем максимальный элемент в массиве и его индекс
    */
    *max = INT_MIN;
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] > *max) {
            *max = array[i];
            if (max_index) {
                *max_index = i;
            }
        }
    }
}


void swap(int* a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void quick_sort(int* main_array, int* side_array, int size){
    int down = 0;
    int up = size - 1;
    int pivot = main_array[size / 2];
    if (size > 1){
        while (down <= up){
            while (main_array[down] < pivot) down++;
            while (pivot < main_array[up]) up--;
            if (down <= up){
                swap(&main_array[down], &main_array[up]);
                swap(&side_array[down], &side_array[up]);
                down++;
                up--;
            }
        }
        quick_sort(main_array, side_array, up + 1);
        quick_sort(main_array + down, side_array + down, size - down);
    }
}


void fight(int team1, int team2, int* winner, int* loser) {
    /*
     Выбираем из двух команд победителя и проигравшего
    */
    if (team1 > team2) {
        *winner = team1;
        *loser = team2;
    } else {
        *winner = team2;
        *loser = team1;
    }
}


int main(void) {
    int value;
    int N;
    int Q;
    scanf("%i", &N);
    int i;
    Queue* queue = init_queue(N);
    for (i = 0; i < N; i++) {
        scanf("%i", &value);
        push(queue, &value);
    }
    scanf("%i", &Q);
    /*
    * rhymes - массив со считалками
    * indices - массив индексов, который мы отсортируем вместе с rhymes,
    чтобы потом восстановить порядок. Rhymes мы отсортируем, чтобы в цикле
    не искать постоянно считалку под текущий шаг, а просто сдвигаться по порядку.
    * teams1 и teams2 - массивы, в которые мы на места, соответствующие
    считалкам из rhymes будем класть команды на данном шаге
    * answers1 и answers2 - в них кладем команды после обратной сортировки
    с помощью индексов из indices
    */
    int* rhymes = calloc(Q, sizeof(int));
    int* indices = calloc(Q, sizeof(int));
    int* teams1 = calloc(Q, sizeof(int));
    int* teams2 = calloc(Q, sizeof(int));
    int* answers1 = calloc(Q, sizeof(int));
    int* answers2 = calloc(Q, sizeof(int));
    for (i = 0; i < Q; i++) {
        scanf("%i", &rhymes[i]);
        indices[i] = i;
    }
    int team1;
    int team2;
    int winner;
    int loser;
    int last_game;
    array_max(rhymes, Q, &last_game, NULL);
    int rhyme_index = 0;
    int max_team = 0;
    int max_team_index = 0;
    array_max(queue->values, N, &max_team, &max_team_index);
    // printf("max_team: %i\n", max_team);
    // printf("max_team_index: %i\n", max_team_index);
    quick_sort(rhymes, indices, Q);
    pop(queue, &team1);
    i = 0;
    while (i <= max_team_index) {
        /*
        Идем по очереди до максимальной по величине команды, после
        этого участники игры будут повторятся с периодом N - 1, т. к. одна
        команда (с наибольшим значением) играет всегда, и ее мы вычитаем
        */
        // printf("STEP");
        pop(queue, &team2);
        while (rhyme_index < Q && i == rhymes[rhyme_index] - 1) {
            teams1[rhyme_index] = team1;
            teams2[rhyme_index] = team2;
            rhyme_index++;
        }
        // printf("rhyme_index: %i\n", rhyme_index);
        fight(team1, team2, &winner, &loser);
        push(queue, &loser);
        team1 = winner;
        i++;
    }
    int games_played = i;
    int cycle_len = N - 1;
    int offset;
    while (rhyme_index < Q) {
        offset = (rhymes[rhyme_index] - games_played - 1) % cycle_len;
        // printf("offset: %i\n", offset);
        teams1[rhyme_index] = max_team;
        // printf("front + offset: %i\n", queue->front + offset);
        value = queue->values[norm_index(queue, queue->front + offset)];
        teams2[rhyme_index] = value;
        // printf("value: %i\n", value);
        rhyme_index++;
    }
    for (i = 0; i < Q; i++) {
        answers1[indices[i]] = teams1[i];
        answers2[indices[i]] = teams2[i];
    }
    for (i = 0; i < Q; i++) {
        printf("%i %i\n", answers1[i], answers2[i]);
    }
    free(queue->values);
    free(queue);
    free(indices);
    free(teams1);
    free(teams2);
    free(answers1);
    free(answers2);
    free(rhymes);
}