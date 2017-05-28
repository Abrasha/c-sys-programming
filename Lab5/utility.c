#include "utility.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "constants.h"
#include <poll.h>

char getByte(int number, int n) {
    return (char) (number >> (8 * n)) & 0xFF;
}


struct pollfd *createPollfd(int fd, short events) {
    struct pollfd *pfds = malloc(sizeof(struct pollfd));
    pfds->fd = fd;
    pfds->events = events;
    return pfds;
}

void handleError() {
    printf("%s\n", strerror(errno));
    exit(1);
}

void printBytes(const char *array, int size, int blockSize) {
    for (int i = 0; i < size; i++) {
        if (i % blockSize == 0) printf("\n");
        printf("%02X", array[i] & 0xFF); //clears all but 1byte
    }
    printf("\n");
}

const char *getParameter(const char *paramName, int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(paramName, argv[i]) == 0) {
            return argv[i + 1];
        }
    }
    return empty;
}

int checkMode(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(recieveModeParam, argv[i]) == 0) {
            return recieveMode;
        } else if (strcmp(transmitModeParam, argv[i]) == 0) {
            return transmitMode;
        }
    }
    return -1;
}


//get opt?
const InputParameters *getParams(int argc, char **argv) {
    InputParameters *params = malloc(sizeof(InputParameters));
    const char *file = getParameter(fileparam, argc, argv);
    if (strcmp(file, empty) == 0) params->dest_file = defaultFile;
    else params->dest_file = file;

    const char *pipe = getParameter(pipeparam, argc, argv);
    if (strcmp(pipe, empty) == 0) params->pipe_file = defaultPipe;
    else params->pipe_file = pipe;

    int mode = checkMode(argc, argv);
    if (mode < 0) {
        printf("Wrong execution_mode param (-r -t)\n");
        exit(-1);
    }
    params->execution_mode = mode;
    return params;
}

