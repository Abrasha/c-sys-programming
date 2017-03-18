#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdbool.h>

#define STD_IN 0
#define BUFFER_SIZE 512

#define TIMEOUT_SEC 5
#define TIMEOUT_USEC 0

void validateArgc(int argc){
    if (argc < 2) {
        fprintf(stderr, "Too few arguments specified: %d", argc);
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        fprintf(stderr, "Too many arguments specified: %d", argc);
        exit(EXIT_FAILURE);
    }
}

void zeroTimeout(struct timeval *timeout) {
    timeout->tv_sec = TIMEOUT_SEC;
    timeout->tv_usec = TIMEOUT_USEC;
}

int main(int argc, char *argv[]) {

    int fd = STDIN_FILENO;
    char buf[BUFFER_SIZE];
    struct timeval timeout;
    int randomFd = 42;
    char *label;
    fd_set fds;

    validateArgc(argc);

    label = argv[1];

    bool running = true;

    while (running) {
        int sret;

        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        zeroTimeout(&timeout);

        sret = select(randomFd, &fds, NULL, NULL, &timeout);
        printf("select returned value: %d\n", sret);

        if (sret == 0) {
            fprintf(stderr, "select timeout. errno = %d\n", errno);
        } else {
            int ret;
            ret = read(fd, (void *) buf, BUFFER_SIZE);
            printf("read %2d symbols: \n", ret);

            if (ret != -1) {
                printf("\t%5s: %s\n", label, buf);
            }

        }

    }

    return EXIT_SUCCESS;

}

