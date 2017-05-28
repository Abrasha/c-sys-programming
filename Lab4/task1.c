#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define LOG_SIZE 1000


char *msg_started = "Logger: started with PID = %d\n";
const char *msg_waiting = "Logger: Waiting 2 seconds\n";
const char *log_filename = "lab3_1.log";


void handleError() {
    printf("%s\n", strerror(errno));
    exit(0);
}


void signal_handler(int signo, siginfo_t *si, /* ignored */ void *ucontext) {
    int logdesc = open(log_filename, O_WRONLY | O_APPEND, 0644);
    char *string_to_log = malloc(LOG_SIZE);

    snprintf(string_to_log,
             LOG_SIZE,
             "Signal number: %d, Signal code: %d, PID of sending process: %d, User id: %d\n",
             si->si_signo, si->si_code, si->si_pid, si->si_uid);
    write(logdesc, string_to_log, strlen(string_to_log));
    free(string_to_log);
    close(logdesc);
}

int main(int argc, char *argv[]) {
    int log_destination = open(log_filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);

    if (log_destination < 0) {
        handleError();
    }

    char *string_to_log = malloc(LOG_SIZE);
    snprintf(string_to_log, LOG_SIZE, msg_started, getpid());
    write(log_destination, string_to_log, LOG_SIZE);
    free(string_to_log);

    struct sigaction act;
    struct sigaction old;
    memset(&act, '\0', sizeof(act));
    act.sa_sigaction = &signal_handler;
    act.sa_flags = SA_SIGINFO;

    if (sigaction(SIGHUP, &act, &old) < 0) {
        handleError();
        return EXIT_FAILURE;
    }

    while (1) {
        sleep(2);
        write(log_destination, msg_waiting, strlen(msg_waiting));
    }

    close(log_destination);
    exit(EXIT_SUCCESS);
}