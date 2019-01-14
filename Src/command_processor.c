//
// Created by Codetector on 1/10/19.
//
#include "command_processor.h"
#include <stdlib.h>

void parse_command(char* command);

void process_command_input_buffer(command_queue* q) {
  if (q->command_queue_length < q->command_queue_capacity) { // Space in the command queue available
    if (q->buffer_length > 0) {
      int16_t command_termination_pos = q->buffer_head;
      char* processing_buffer = malloc(sizeof(char) * q->buffer_length);
      uint16_t pbuffer_length = 0;
      if (processing_buffer == NULL) {
        return;
      }
      for (uint16_t i = 0; i < q->buffer_length; i++) {
        int16_t calculated_index = (q->buffer_head + i) % q->buffer_capacity;
        char current_char = *(q->input_buffer + calculated_index);
        if (current_char == '\r' || current_char == '\n') {
          if (pbuffer_length > 0) {
            processing_buffer[pbuffer_length++] = '\0';
            q->buffer_head = (int16_t) ((calculated_index + 1) % q->buffer_capacity);
            q->buffer_length -= pbuffer_length;
            parse_command(processing_buffer);
            free(processing_buffer);
            break;
          }
        } else {
          processing_buffer[pbuffer_length++] = current_char;
        }
      }
    }
  }
}

void parse_command(char* command) {
//  sscanf(command, "%")
}