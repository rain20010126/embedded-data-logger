#include <stdio.h>
#include "ring_buffer.h"

int main() {
    RingBuffer rb;

    if (rb_init(&rb, 5) != 0) {
        printf("Init failed\n");
        return -1;
    }

    printf("Pushing...\n");
    for (int i = 1; i <= 4; i++) {
        if (rb_push(&rb, i) == 0)
            printf("push %d\n", i);
        else
            printf("push failed (full)\n");
    }

    printf("\nPopping...\n");
    int val;
    while (!rb_empty(&rb)) {
        rb_pop(&rb, &val);
        printf("pop %d\n", val);
    }

    rb_free(&rb);
    return 0;
}