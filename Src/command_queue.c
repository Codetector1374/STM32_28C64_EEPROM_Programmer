//
// Created by Codetector on 1/8/19.
//
#include "command_queue.h"
#include <stdlib.h>
#include <string.h>

command_queue* command_queue_create_v(){
  return command_queue_create_ii(COMMAND_QUEUE_DEFAULT_BUFFER_SIZE, COMMAND_QUEUE_DEFAULT_SIZE);
}

command_queue* command_queue_create_ii(uint8_t buffer_size, uint8_t queue_size) {
  command_queue* q = malloc(sizeof(command_queue));
  if (q == NULL) {
    return NULL;
  }
  q->input_buffer = malloc(sizeof(char) * buffer_size);
  if (q->input_buffer == NULL) {
    free(q);
    return NULL;
  }
  q->buffer_size = buffer_size;
  q->buffer_head = 0;
  q->buffer_tail = 0;

  q->cmd_queue= malloc(sizeof(pgmr_command) * queue_size);
  if (q->cmd_queue == NULL) {
    free(q->input_buffer);
    free(q);
    return NULL;
  }
  q->command_queue_size = queue_size;
  q->command_queue_head = 0;
  q->command_queue_tail = 0;

  return q;
}

void process_data(command_queue* q, char* data, uint8_t len) {
  uint8_t new_tail = q->buffer_tail + len;
  if (new_tail < q->buffer_size && new_tail < q->buffer_head) {
    // The buffer can fit the data
    memcpy(q->input_buffer + q->buffer_tail, data, len);
    return;
  }
  if (new_tail)
}