#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>  // for size_t

typedef struct {
    int *buffer;      // dynamically allocated array
    size_t head;      // write index
    size_t tail;      // read index
    size_t capacity;  // max size
} RingBuffer;

// initialize ring buffer
int rb_init(RingBuffer *rb, size_t capacity);

// free memory
void rb_free(RingBuffer *rb);

// push data into buffer
int rb_push(RingBuffer *rb, int data);

// pop data from buffer
int rb_pop(RingBuffer *rb, int *data);

// check if empty
int rb_empty(RingBuffer *rb);

// check if full
int rb_full(RingBuffer *rb);

#endif