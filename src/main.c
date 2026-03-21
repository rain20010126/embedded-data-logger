#include <stdio.h>
#include "ring_buffer.h"
#include "logger.h"
#include "sensor_data.h"
#include "temp_sensor.h"

uint32_t fake_time = 0;

void pc_output(const char *msg) {
    printf("%s", msg);
}

int main() {
    ring_buffer_t rb;
    logger_t logger;

    rb_init(&rb, 10);
    logger_init(&logger, &rb, pc_output);

    while (1) {
        // 1. read sensor
        sensor_data_t data;
        data.temperature = temp_sensor_read();
        data.timestamp = fake_time++;

        // 2. push to buffer
        rb_push(&rb, data);

        // 3. process logger
        logger_process(&logger);
    }

    return 0;
}