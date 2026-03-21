#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer.h"

// initialize ring buffer
int rb_init(ring_buffer_t *rb, size_t capacity) {
    if (capacity < 2) return -1;  // need at least 2 slots

    rb->buffer = (int *)malloc(sizeof(int) * capacity);
    if (rb->buffer == NULL) return -1;

    rb->head = 0;
    rb->tail = 0;
    rb->capacity = capacity;

    return 0;
}

// free memory
void rb_free(ring_buffer_t *rb) {
    free(rb->buffer);
    rb->buffer = NULL;
}

// check if empty
int rb_empty(ring_buffer_t *rb) {
    return rb->head == rb->tail;
}

// check if full
int rb_full(ring_buffer_t *rb) {
    return (rb->head + 1) % rb->capacity == rb->tail;
}

// push data
int rb_push(ring_buffer_t *rb, int data) {
    if (rb_full(rb)) {
        return -1;  // buffer full
    }

    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % rb->capacity;

    return 0;
}

// pop data
int rb_pop(ring_buffer_t *rb, int *data) {
    if (rb_empty(rb)) {
        return -1;  // buffer empty
    }

    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;

    return 0;
}