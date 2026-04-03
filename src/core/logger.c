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

            int temp = data.sensor.temperature;

            int integer = temp / 100;
            int decimal = abs(temp % 100);

            uint32_t sec = data.timestamp / 1000;
            uint32_t ms  = data.timestamp % 1000;

            snprintf(buf, sizeof(buf),
                    "[t=%lu.%03lus] T=%d.%02d\r\n",
                    sec,
                    ms,
                    integer,
                    decimal);

            logger->output(buf);
        }
    }
}