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

1. **Clone the repository:**

   `got clone https://github.com/petrcernyy/sht30_library`

2. **Change the CMakeList.txt:**

   Inside the examples folder change the CMakeText in ./main to include the correct path to the library.
   
   ```c
   idf_component_register(SRCS "freertos_periodic.c" "~/esp/sht30_library/component/sht30.c"
                    INCLUDE_DIRS "." "~/esp/sht30_library/component")

4. **Build and Flash:**

   Build and flash your project using the ESP-IDF build tools. Make sure that the SHT30 sensor is properly connected to the I2C bus and powered.

1. **Second option:**

   Simply copy the sht30.c and sht30.h to your project directory.


## Example Usage

Here's an example of how to use the library to perform a single-shot measurement and read temperature and humidity:

```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "sht30.h"

#define SCL_PIN 8
#define SDA_PIN 9
#define I2C_PORT 0
#define I2C_SPEED 10000

static const char *TAG = "MAIN";

void app_main(void)
{

    sht30_t sht30;

    sht30_init(&sht30, I2C_PORT, SCL_PIN, SDA_PIN, SHT30_ADDRESS_DEF, I2C_SPEED, MAX_WAIT_TIME);
    sht30_heater_control(&sht30, Heater_Disable);

    float temperature;
    float humidity;

    sht30_single_shot(&sht30, Repeatability_High, ClockStretching_Disable);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );

    temperature = sht30_read_temperature_celsius(&sht30);
    humidity = sht30_read_humidity(&sht30);
    ESP_LOGI(TAG, "Temperature is %.2f celsius", temperature);
    ESP_LOGI(TAG, "Humidity is %.2f", humidity);

}

