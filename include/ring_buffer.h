#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>  // for size_t

typedef struct {
    int *buffer;      // dynamically allocated array
    size_t head;      // write index
    size_t tail;      // read index
    size_t capacity;  // max size
} ring_buffer_t;

// initialize ring buffer
int rb_init(ring_buffer_t *rb, size_t capacity);

// free memory
void rb_free(ring_buffer_t *rb);

// push data into buffer
int rb_push(ring_buffer_t *rb, int data);

// pop data from buffer
int rb_pop(ring_buffer_t *rb, int *data);

// check if empty
int rb_empty(ring_buffer_t *rb);

// check if full
int rb_full(ring_buffer_t *rb);

#endif