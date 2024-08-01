# SHT30 Library for ESP-IDF

This library allows you to interface with the SHT30 temperature and humidity sensor using ESP-IDF version 5.3. It includes functions for initialization, single-shot and periodic measurements, and other sensor controls.

## Features

- **Single Shot Mode:** Performs one measurements.
- **Periodic Mode:** Automatically take measurements at specified intervals.
- **Internal Heater Control:** Enable or disable the sensor's internal heater.

## Files

- `sht30.c`: Contains the implementation of the SHT30 functions.
- `sht30.h`: Header file with function declarations and definitions.
- `examples/`: Directory with example applications demonstrating how to use the library.

## Getting Started

To use the SHT30 library, follow these steps:

1. **Add the Library to Your Project:**

   Copy the `sht30.c` and `sht30.h` files into your project's directory, typically under `components/sht30/` or similar.

2. **Configure Your Project:**

   Ensure that your project is configured to include the I2C driver and that the SHT30 sensor is connected to the I2C bus. Update the I2C configuration parameters as needed.

3. **Build and Flash:**

   Build and flash your project using the ESP-IDF build tools. Make sure that the SHT30 sensor is properly connected to the I2C bus and powered.

## Example Usage

Here's an example of how to use the library to perform a single-shot measurement and read temperature and humidity:

```c
#include "sht30.h"
#include "driver/i2c.h"
#include <stdio.h>

#define I2C_PORT I2C_NUM_0
#define SDA_PIN 21
#define SCL_PIN 22
#define SHT30_ADDR SHT30_ADDRESS_DEF

void app_main(void) {
    sht30_t sensor;
    sht30_status_t status;

    // Initialize the sensor
    status = sht30_init(&sensor, I2C_PORT, SCL_PIN, SDA_PIN, SHT30_ADDR, 100000, 10000);
    if (status != ok) {
        printf("Failed to initialize SHT30 sensor\n");
        return;
    }

    // Perform a single-shot measurement with high repeatability and clock stretching enabled
    status = sht30_single_shot(&sensor, Repeatability_High, ClockStretching_Enable);
    if (status != ok) {
        printf("Failed to perform single-shot measurement\n");
        return;
    }

    // Print temperature and humidity
    float temperature = sht30_read_temperature_celsius(&sensor);
    float humidity = sht30_read_humidity(&sensor);

    printf("Temperature: %.2f°C\n", temperature);
    printf("Humidity: %.2f%%\n", humidity);
}
