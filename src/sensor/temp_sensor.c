#include "temp_sensor.h"
#include <stdlib.h>

float temp_sensor_read(void) {
    return (rand() % 4000);  // 0~40°C
}