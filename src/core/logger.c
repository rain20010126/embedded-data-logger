#include "logger.h"
#include "sensor_data.h"
#include <stdio.h>

void logger_init(logger_t *logger, ring_buffer_t *rb, log_output_func_t output) {
    logger->rb = rb;
    logger->output = output;
}

void logger_process(logger_t *logger) {
    log_data_t data;
    char buf[128];

    while (!rb_empty(logger->rb)) {

        if (rb_pop(logger->rb, &data) == 0) {

            sprintf(buf, "[%u] T=%d.%02d H=%d.%02d P=%d G=%d\n",
                data.timestamp,
                data.sensor.temperature / 100,
                data.sensor.temperature % 100,
                data.sensor.humidity / 100,
                data.sensor.humidity % 100,
                data.sensor.pressure,
                data.sensor.gas);
                
            logger->output(buf);
        }
    }
}