#ifndef LOGGER_H
#define LOGGER_H

#include "ring_buffer.h"

// output abstraction
typedef void (*log_output_func_t)(const char *msg);

typedef struct {
    ring_buffer_t *rb;
    log_output_func_t output;
} logger_t;

void logger_init(logger_t *logger, ring_buffer_t *rb, log_output_func_t output);
void logger_process(logger_t *logger);

#endif