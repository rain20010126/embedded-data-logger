#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <stdint.h>

int sensor_init(void);
int sensor_read(sensor_data_t *data);

#endif