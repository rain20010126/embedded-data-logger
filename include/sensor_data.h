#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <stdint.h>

typedef struct {
    uint32_t timestamp;
    int temperature;
} sensor_data_t;

#endif