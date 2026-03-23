#include "sensor_data.h"
#include "temp_sensor.h"
#include <stdlib.h>
#include "i2c.h"

// BME680 I2C address
#define BME680_ADDR (0x77 << 1)

// calibration parameters
static uint16_t dig_T1;
static int16_t dig_T2;
static int8_t  dig_T3;

static int32_t t_fine;

// read calibration
static int read_calibration(void)
{
    uint8_t buf[2];

    // par_t1 (0xE9, 0xEA)
    uint8_t reg = 0xE9;
    HAL_I2C_Master_Transmit(&hi2c1, BME680_ADDR, &reg, 1, 100);
    HAL_I2C_Master_Receive(&hi2c1, BME680_ADDR, buf, 2, 100);
    dig_T1 = (buf[1] << 8) | buf[0];

    // par_t2 (0x8A, 0x8B)
    reg = 0x8A;
    HAL_I2C_Master_Transmit(&hi2c1, BME680_ADDR, &reg, 1, 100);
    HAL_I2C_Master_Receive(&hi2c1, BME680_ADDR, buf, 2, 100);
    dig_T2 = (buf[1] << 8) | buf[0];

    // par_t3 (0x8C)
    reg = 0x8C;
    HAL_I2C_Master_Transmit(&hi2c1, BME680_ADDR, &reg, 1, 100);
    HAL_I2C_Master_Receive(&hi2c1, BME680_ADDR, buf, 1, 100);
    dig_T3 = (int8_t)buf[0];

    return 0;
}

int sensor_init(void)
{
    uint8_t reg, val;

    // set oversampling
    reg = 0x74; // ctrl_meas
    val = 0x2C; // temp x2, forced mode

    if (HAL_I2C_Master_Transmit(&hi2c1, BME680_ADDR, &reg, 1, 100) != HAL_OK)
        return -1;

    if (HAL_I2C_Master_Transmit(&hi2c1, BME680_ADDR, &val, 1, 100) != HAL_OK)
        return -1;

    return read_calibration();
}

int sensor_read(sensor_data_t *data)
{
    uint8_t reg = 0x22;
    uint8_t buf[3];

    // raw temperature
    if (HAL_I2C_Master_Transmit(&hi2c1, BME680_ADDR, &reg, 1, 100) != HAL_OK)
        return -1;

    if (HAL_I2C_Master_Receive(&hi2c1, BME680_ADDR, buf, 3, 100) != HAL_OK)
        return -1;

    int32_t adc_T =
    (buf[0] << 12) |
    (buf[1] << 4) |
    (buf[2] >> 4);

    // datasheet formula
    int32_t var1 = ((int32_t)adc_T >> 3) - ((int32_t)dig_T1 << 1);
    int32_t var2 = (var1 * (int32_t)dig_T2) >> 11;
    int32_t var3 = (((var1 >> 1) * (var1 >> 1)) >> 12) * ((int32_t)dig_T3 << 4) >> 14;

    t_fine = var2 + var3;

    int32_t temp_comp = ((t_fine * 5) + 128) >> 8;

    // convert to float
    data->temperature = temp_comp / 100.0f;

    return 0;
}