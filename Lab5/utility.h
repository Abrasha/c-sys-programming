#include <stdint.h>
#include <stddef.h>

typedef struct InputParameters {
    const char *dest_file;
    const char *pipe_file;
    int execution_mode;
} InputParameters;

char getByte(int, int);

void handleError();

const InputParameters *getParams(int, char **);

int checkMode(int, char **);

const char *getParameter(const char *, int, char **);

void printBytes(const char *array, int size, int blockSize);

uint16_t crc16(uint16_t crc, const void *buf, size_t size);

struct pollfd *createPollfd(int fd, short events);
