#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>  // for size_t
#include "sensor_data.h"

typedef struct {
    sensor_data_t *buffer;
    size_t head;
    size_t tail;
    size_t capacity;
    size_t size;
} ring_buffer_t;

// initialize ring buffer
int rb_init(ring_buffer_t *rb, size_t capacity);

// free memory
void rb_free(ring_buffer_t *rb);

// push data into buffer
int rb_push(ring_buffer_t *rb, sensor_data_t data);

// pop data from buffer
int rb_pop(ring_buffer_t *rb, sensor_data_t *data);

// check if empty
int rb_empty(ring_buffer_t *rb);

// check if full
int rb_full(ring_buffer_t *rb);

#endif