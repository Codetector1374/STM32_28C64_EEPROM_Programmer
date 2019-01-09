//
// Created by Codetector on 1/8/19.
//
#include "command_queue.h"

command_queue* command_queue_create_v(){
  return command_queue_create_ii(COMMAND_QUEUE_DEFAULT_BUFFER_SIZE, COMMAND_QUEUE_DEFAULT_SIZE);
}

command_queue* command_queue_create_ii(uint8_t buffer_size, uint8_t queue_size) {

}