#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <time.h>

#define SHARED_MEM_ADDR "/sharemmemory"
#define BUFF_SIZE 64

typedef struct datum {
    int pid;
    long time;
    char str[BUFF_SIZE];
} my_datum;

void handleError() {
    printf("%s\n", strerror(errno));
    exit(0);
}

int main(int argc, char *argv[]) {
    int shm_open_fd = shm_open(SHARED_MEM_ADDR, O_RDWR | O_CREAT, 0777);
    if (shm_open_fd == 1) { handleError(); }

    struct datum *res = mmap(NULL, sizeof(my_datum), PROT_READ | PROT_WRITE, MAP_SHARED, shm_open_fd, 0);

    if (res == (void *) -1) {
        handleError();
    }

    ftruncate(shm_open_fd, sizeof(my_datum));

    while (1) {
        char read_data[100];
        scanf("%s", read_data);
        printf("Old Datum: pid %d, time %ld, text: %s\n", res->pid, res->time, res->str);
        msync(res, sizeof(struct datum), MS_SYNC);
        strcpy(res->str, read_data);
        res->pid = getpid();
        res->time = time(0);
        printf("New Datum: pid %d, time %ld, text: %s\n", res->pid, res->time, res->str);
    }
    close(shm_open_fd);
    shm_unlink(SHARED_MEM_ADDR);
    return 0;

}

