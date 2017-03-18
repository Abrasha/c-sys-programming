#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ASCII_SHIFT 'a' - 'A'

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

    char *inputFilename;
    char *outputFilename;
    char *line = NULL;
    FILE *out;
    FILE *in;

    _IO_ssize_t count = 0;
    size_t readCount = 0;

    statistics *stats;

    if (argc < 3) {
        fprintf(stderr, "Too few arguments specified: %d", argc);
        exit(EXIT_FAILURE);
    } else if (argc > 3) {
        fprintf(stderr, "Too many arguments specified: %d", argc);
        exit(EXIT_FAILURE);
    }

    printf("Starting execution!\n");

    inputFilename = argv[1];
    in = openInputFile(inputFilename);
    if (in == NULL) {
        fprintf(stderr, "Error reading input file: %s", inputFilename);
        exit(EXIT_FAILURE);
    }

    outputFilename = argv[2];
    out = openOutputFile(outputFilename);
    if (out == NULL) {
        fprintf(stderr, "Error opening / creating output file: %s", outputFilename);
    }

    stats = malloc(sizeof(statistics));
    stats->readLines = 0;
    stats->modifiedBits = 0;

    while ((count = getline(&line, &readCount, in)) != -1) {
        size_t s_len;
        int i;
        printf("Read symbols: %lu | ", readCount);
        printf("Read count: %lu | ", count);
        printf("Read line: %s;", line);

        stats->readLines++;

        s_len = strlen(line);
        for (i = 0; i < s_len; ++i) {
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

