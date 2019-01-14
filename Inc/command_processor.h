//
// Created by Codetector on 1/10/19.
//

#ifndef INC_28C64PROGRAMMER_COMMAND_PROCESSOR_H
#define INC_28C64PROGRAMMER_COMMAND_PROCESSOR_H

#include "usart.h"
#include "command_queue.h"

void process_command_input_buffer(command_queue* q);

#endif //INC_28C64PROGRAMMER_COMMAND_PROCESSOR_H
