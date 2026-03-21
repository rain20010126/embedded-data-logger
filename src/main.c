#include <stdio.h>
#include "ring_buffer.h"
#include "logger.h"
#include "sensor_data.h"

void pc_output(const char *msg) {
    printf("%s", msg);
}

int main() {
    ring_buffer_t rb;
    logger_t logger;

    rb_init(&rb, 10);
    logger_init(&logger, &rb, pc_output);

    // fake sensor data
    for (int i = 0; i < 5; i++) {
        sensor_data_t data;
        data.timestamp = i;
        data.temperature = 25.0 + i;

        rb_push(&rb, data);
    }

    logger_process(&logger);

    return 0;
}