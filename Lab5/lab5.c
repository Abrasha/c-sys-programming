#include <stdio.h>
#include "constants.h"
#include "utility.h"
#include "transmitter.h"
#include "reciever.h"


int main(int argc, char **argv) {
    const InputParameters *program_args = getParams(argc, argv);
    if (program_args->execution_mode == recieveMode) {
        fprintf(stdout, "Starting in receiving mode");
        recieve(program_args->dest_file, program_args->pipe_file);
    } else if (program_args->execution_mode == transmitMode) {
        printf("Starting in transmitting mode");
        transmit(program_args->dest_file, program_args->pipe_file);
    }


}




