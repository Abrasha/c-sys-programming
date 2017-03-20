#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define CHILD_SLEEP_SEC 5

void print_process_metadata(const char *title_msg);

int main(int argc, char *argv[]) {

    __pid_t forked_id;

    print_process_metadata("Starting process with data:");

    forked_id = fork();

    if (forked_id == -1) {
        printf("Error forking new process. Error code: %d", errno);
        exit(EXIT_FAILURE);
    }

    if (forked_id == 0) {
        print_process_metadata("Child process");
        sleep(CHILD_SLEEP_SEC);
    } else {
        int exit_status = 0;
        print_process_metadata("Parent process:");
        printf("Forked pid: %d\n", forked_id);
        /* wait for all child processes to die */
        /* POSIX: http://stackoverflow.com/q/19461744/5091346 */
        wait(NULL);
        printf("Child process died with status: %d", exit_status);
    }


    exit(EXIT_SUCCESS);
}

void print_process_metadata(const char *title_msg) {
    __pid_t pid;
    __pid_t sid;
    __pid_t gid;

    printf("====================\n");
    fputs(title_msg, stdout);
    fputs("\n", stdout);

    pid = getpid();
    sid = getsid(pid);
    gid = getgid();

    printf("\tpid = %d\n", pid);
    printf("\tsid = %d\n", sid);
    printf("\tgid = %d\n", gid);
    printf("====================\n");
}
