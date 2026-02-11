#include <stdio.h>
#include <stdlib.h>


typedef struct Deque {
    int front;
    int back;
    int capacity;
    int* values;
} Deque;


int norm_index(Deque* deque, int index) {
    return (index % deque->capacity + deque->capacity) % deque->capacity;
}


int is_full(Deque* deque) {
    if (!deque) {
        return 0;
    }
    return deque->back - deque->front == deque->capacity;
}


int is_empty(Deque* deque) {
    if (!deque) {
        return 0;
    }
    return deque->front == deque->back;
}


void expand(Deque* deque) {
    if (!deque) {
        return;
    }
    deque->front = norm_index(deque, deque->front);
    deque->back = norm_index(deque, deque->back);
    int old_capacity = deque->capacity;
    deque->capacity *= 2;
    int* tmp_values = realloc(deque->values, deque->capacity * sizeof(int));
    if (!tmp_values) {
        return;
    }
    deque->values = tmp_values;
    int i;
    if (deque->front >= deque->back) {
        for (i = 0; i < deque->back; i++) {
            deque->values[i + old_capacity] = deque->values[i];
        }
        deque->back += old_capacity;
    }
}


int push_front(Deque* deque, int* value) {
    if (!deque || !value) {
        return -1;
    }
    if (is_full(deque)) {
        expand(deque);
    }
    deque->front--;
    deque->values[norm_index(deque, deque->front)] = *value;
    return 0;
}


int push_back(Deque* deque, int* value) {
    if (!deque || !value) {
        return -1;
    }
    if (is_full(deque)) {
        expand(deque);
    }
    deque->values[norm_index(deque, deque->back)] = *value;
    deque->back++;
    return 0;
}


int pop_front(Deque* deque, int* value) {
    if (!deque || !value) {
        return -1;
    }
    *value = deque->values[norm_index(deque, deque->front)];
    deque->front++;
    return 0;
}


int pop_back(Deque* deque, int* value) {
    if (!deque || !value) {
        return -1;
    }
    deque->back--;
    *value = deque->values[norm_index(deque, deque->back)];
    return 0;
}


int front(Deque* deque, int* value) {
    if (!deque || !value) {
        return -1;
    }
    *value = deque->values[norm_index(deque, deque->front)];
    return 0;
}


int back(Deque* deque, int* value) {
    if (!deque) {
        return -1;
    }
    *value = deque->values[norm_index(deque, deque->back - 1)];
    return 0;
}


int clear(Deque* deque) {
    if (!deque) {
        return -1;
    }
    deque->front = 0;
    deque->back = 0;
    return 0;
}


int check_deque(Deque* deque) {
    int true_false = is_empty(deque);
    if (true_false) {
        printf("error\n");
    }
    return !true_false;
}


Deque* init_deque(void) {
    Deque* deque = malloc(sizeof(Deque));
    deque->front = 0;
    deque->back = 0;
    deque->capacity = 100;
    deque->values = (int*)calloc(deque->capacity, sizeof(int));
    return deque;
}


int is_str_equal(char* sample, char* command) {
    int i = 0;
    while (command[i] != '\0') {
        if (command[i] != sample[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}


int main(void) {
    int value;
    char command[20];
    Deque* deque = init_deque();
    scanf("%s", command);
    while (!is_str_equal("exit", command)) {
        if (is_str_equal("push_front", command)) {
            scanf(" %d", &value);
            push_front(deque, &value);
            printf("ok\n");
        } else if (is_str_equal("push_back", command)) {
            scanf(" %d", &value);
            push_back(deque, &value);
            printf("ok\n");
        } else if (is_str_equal("pop_front", command)) {
            if (check_deque(deque)) {
                pop_front(deque, &value);
                printf("%d\n", value);
            }
        } else if (is_str_equal("pop_back", command)) {
            if (check_deque(deque)) {
                pop_back(deque, &value);
                printf("%d\n", value);
            }
        } else if (is_str_equal("front", command)) {
            if (check_deque(deque)) {
                front(deque, &value);
                printf("%d\n", value);
            }
        } else if (is_str_equal("back", command)) {
            if (check_deque(deque)) {
                back(deque, &value);
                printf("%d\n", value);
            }
        } else if (is_str_equal("size", command)) {
            printf("%d\n", deque->back - deque->front);
        } else if (is_str_equal("clear", command)) {
            clear(deque);
            printf("ok\n");
        }
        scanf("%s", command);
    }
    free(deque->values);
    free(deque);
    printf("bye\n");
    return 0;
}
