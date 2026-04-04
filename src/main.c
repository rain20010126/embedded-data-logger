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

    sensor_init(); 

    uint32_t fake_time = 0;

    while (1) {
        log_data_t log;

        // 1. read sensor
        if (sensor_read_temperature(&log.sensor) != 0) {
            continue;
        }

        // 2. add timestamp（system layer）
        log.timestamp = fake_time++;

        // 3. push to buffer
        rb_push(&rb, log);

        // 4. process logger
        logger_process(&logger);
    }

    return 0;
}