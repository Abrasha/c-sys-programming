#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Too few arguments specified: %d", argc);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

