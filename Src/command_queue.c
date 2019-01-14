//
// Created by Codetector on 1/8/19.
//
#include "command_queue.h"
#include <stdlib.h>
#include <string.h>

command_queue* command_queue_create_v(){
  return command_queue_create_ii(COMMAND_QUEUE_DEFAULT_BUFFER_SIZE, COMMAND_QUEUE_DEFAULT_SIZE);
}

command_queue* command_queue_create_ii(int16_t buffer_size, int16_t queue_size) {
  command_queue* q = malloc(sizeof(command_queue));
  if (q == NULL) {
    return NULL;
  }
  q->input_buffer = malloc(sizeof(char) * buffer_size);
  if (q->input_buffer == NULL) {
    free(q);
    return NULL;
  }
  q->buffer_capacity = buffer_size;
  q->buffer_length = 0;
  q->buffer_head = 0;
  q->buffer_tail = 0;

  q->cmd_queue= malloc(sizeof(pgmr_command) * queue_size);
  if (q->cmd_queue == NULL) {
    free(q->input_buffer);
    free(q);
    return NULL;
  }
  q->command_queue_capacity = queue_size;
  q->command_queue_length = 0;
  q->command_queue_head = 0;
  q->command_queue_tail = 0;

  return q;
}

void command_queue_process_data(command_queue* q, char* data, uint8_t len) {
  int16_t remain = q->buffer_capacity - q->buffer_length;
  if (remain < len){
    len = (uint8_t)remain; // This is designed to drop data;
  }
  if (q->buffer_length == 0 || (q->buffer_tail > q->buffer_head  && q->buffer_capacity - q->buffer_tail >= len)) {
    memcpy(q->input_buffer + q->buffer_tail, data, len);
  } else {
    int16_t firstBatchCopy = q->buffer_capacity - q->buffer_tail;
    if (firstBatchCopy > 0) {
      memcpy(q->input_buffer + q->buffer_tail, data, (uint16_t)firstBatchCopy);
    }
    memcpy(q->input_buffer, data + firstBatchCopy, (uint16_t)(len - firstBatchCopy));
  }
  q->buffer_length += len;
}