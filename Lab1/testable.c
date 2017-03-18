#include <stdio.h>
#include <stdlib.h>

int fact(int number) {
    if (number == 0 || number == 1) {
        return number;
    }
    return fact(number - 1) * number;
}

int combine(int n, int k) {
    return fact(n) / (fact(k), fact(n - k));
}

void print(int deep, int *array, int count) {
    int i = 0;
    for (; i < count; ++i) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

void showPyramid(int deep) {
    int currentLevel = 1;
    int i = 0;

    int *old = malloc(sizeof(int) * currentLevel);
    print(deep, old, currentLevel);

    for (; i < deep; ++i) {
        int *new = malloc(sizeof(int) * currentLevel);
        int y = 0;

        new[y++] = 1;
        new[currentLevel - 1] = 1;

        for (; y < currentLevel - 1; y++) {
            new[y] = old[y - 1] + old[y];
        }

        free(old);
        old = new;
        print(deep, old, currentLevel);

        currentLevel++;
    }

    free(old);
}

int main(int argc, char *argv[]) {

    int count;

    if (argc != 2) {
        fprintf(stderr, "Too few arguments specified: %d", argc);
        exit(EXIT_FAILURE);
    }

    count = atoi(argv[1]);

    printf("Requested %d rows", count);

    showPyramid(count);

    exit(EXIT_SUCCESS);
}

