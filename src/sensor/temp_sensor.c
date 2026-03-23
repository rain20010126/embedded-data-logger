#include "sensor_data.h"
#include "temp_sensor.h"
#include <stdlib.h>
// TODO: include bme680 driver later

int sensor_read(sensor_data_t *data)
{
    // TODO: replace with real BME680 reading

    // temporary fake (for integration)
    data->temperature = 2500;
    data->humidity    = 5000;
    data->pressure    = 101325;
    data->gas         = 10000;

    return 0;
}

void sensor_init(void)
{
    // TODO: init BME680 (I2C, calibration, etc.)
}