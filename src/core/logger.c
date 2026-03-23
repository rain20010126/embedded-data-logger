#include "logger.h"
#include "sensor_data.h"
#include <stdio.h>

void logger_init(logger_t *logger, ring_buffer_t *rb, log_output_func_t output) {
    logger->rb = rb;
    logger->output = output;
}

void logger_process(logger_t *logger) {
    sensor_data_t data;
    char buf[64];

    while (!rb_empty(logger->rb)) {

        if (rb_pop(logger->rb, &data) == 0) {

            sprintf(buf, "[%u] temp=%d.%02d\n",
                    data.timestamp,
                    data.temperature / 100);

            logger->output(buf);
        }
    }
}