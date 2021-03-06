//
// Created by Codetector on 1/8/19.
//

#ifndef INC_28C64PROGRAMMER_COMMAND_QUEUE_H
#define INC_28C64PROGRAMMER_COMMAND_QUEUE_H

#include <stdint.h>

#ifndef COMMAND_QUEUE_DEFAULT_BUFFER_SIZE
#define COMMAND_QUEUE_DEFAULT_BUFFER_SIZE 64
#endif

#ifndef COMMAND_QUEUE_DEFAULT_SIZE
#define COMMAND_QUEUE_DEFAULT_SIZE 16
#endif

enum pgmr_command_type {
    pgmr_command_type_read, pgmr_command_type_write
};

typedef struct pgmr_command {
    enum pgmr_command_type command_type;
    uint16_t address;
    uint8_t data;
} pgmr_command;

typedef struct command_queue {
    char* input_buffer;
    int16_t buffer_capacity;
    int16_t buffer_length;
    int16_t buffer_head;
    int16_t buffer_tail;

    pgmr_command* cmd_queue;
    int16_t command_queue_capacity;
    int16_t command_queue_length;
    int16_t command_queue_head;
    int16_t command_queue_tail;
} command_queue;

command_queue* command_queue_create_v();

command_queue* command_queue_create_ii(int16_t buffer_size, int16_t queue_size);

void command_queue_process_data(command_queue* q, char* data, uint8_t len);

uint8_t command_avail(command_queue* q);
pgmr_command* command_queue_peek(command_queue* q);
void command_queue_remove(command_queue* q);

#endif //INC_28C64PROGRAMMER_COMMAND_QUEUE_H
