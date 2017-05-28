
#include <stdio.h>
#include "constants.h"
#include "utility.h"
#include "transmitter.h"
#include "reciever.h"


int main(int argc, char **argv) {
    const InputParameters *params = getParams(argc, argv);
    if (params->execution_mode == recieveMode) {
        printf("Starting in receiving execution_mode");
        recieve(params->dest_file, params->pipe_file);
    } else if (params->execution_mode == transmitMode) {
        printf("Starting in transmitting execution_mode");
        transmit(params->dest_file, params->pipe_file);
    }


}




