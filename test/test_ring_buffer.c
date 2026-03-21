#include <stdio.h>
#include "ring_buffer.h"
#include "sensor_data.h"

int main() {
    ring_buffer_t rb;

    if (rb_init(&rb, 5) != 0) {
        printf("Init failed\n");
        return -1;
    }

    printf("Pushing...\n");

    // push sensor_data_t instead of int
    for (int i = 0; i < 6; i++) {
        sensor_data_t data;

        data.timestamp = i * 100;     // fake timestamp
        data.temperature  = 2500 + i;    // e.g. 25.00°C → 2500

        if (rb_push(&rb, data) == 0)
            printf("push t=%u temp=%.2f\n",
                   data.timestamp,
                   data.temperature / 100.0);
        else
            printf("push failed (full)\n");
    }

    printf("\nPopping...\n");

    sensor_data_t val;

    while (!rb_empty(&rb)) {
        rb_pop(&rb, &val);

        printf("pop t=%u temp=%.2f\n",
               val.timestamp,
               val.temperature / 100.0);
    }

    rb_free(&rb);
    return 0;
}