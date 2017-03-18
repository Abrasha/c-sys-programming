#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ASCII_SHIFT 'A' - 'a'

FILE *openInputFile(char *filename) {
    return fopen(filename, "r");
}

FILE *openOutputFile(char *filename) {
    return fopen(filename, "w");
}

struct _statistics {
    int readLines;
    int modifiedBits;
};

typedef struct _statistics statistics;

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Too few arguments specified: %d", argc);
        exit(EXIT_FAILURE);
    } else if (argc > 3){
        fprintf(stderr, "Too many arguments specified: %d", argc);
        exit(EXIT_FAILURE);
    }

    printf("Starting execution!\n");

    char *inputFilename = argv[1];
    FILE *in = openInputFile(inputFilename);
    if (in == NULL) {
        fprintf(stderr, "Error reading input file: %s", inputFilename);
        exit(EXIT_FAILURE);
    }

    char *outputFilename = argv[2];
    FILE *out = openOutputFile(outputFilename);
    if (out == NULL) {
        fprintf(stderr, "Error opening / creating output file: %s", outputFilename);
    }

    _IO_ssize_t count = 0;
    size_t readCount = 0;

    statistics *stats = malloc(sizeof(statistics));
    stats->readLines = 0;
    stats->modifiedBits = 0;

    char *line = NULL;
    while ((count = getline(&line, &readCount, in)) != -1) {
        printf("Read symbols: %lu | ", readCount);
        printf("Read count: %lu | ", count);
        printf("Read line: %s;", line);

        stats->readLines++;

        size_t s_len = strlen(line);
        for (int i = 0; i < s_len; ++i) {
            if (isalpha(line[i])) {
                line[i] -= ASCII_SHIFT;
                stats->modifiedBits++;
            }
        }

        fprintf(out, "%s", line);
    }

    fclose(in);
    fclose(out);

    free(line);

    printf("\nSuccessfully read %u lines", stats->readLines);
    printf("\nSuccessfully modified %u characters", stats->modifiedBits);

    free(stats);

    exit(EXIT_SUCCESS);
}

