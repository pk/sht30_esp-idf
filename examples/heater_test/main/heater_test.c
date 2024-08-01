#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "sht30.h"

#define SCL_PIN 8
#define SDA_PIN 9
#define I2C_PORT 0
#define I2C_SPEED 10000

static const char *TAG = "MAIN";
const int startHeater = 20;

void app_main(void)
{

    sht30_t sht30;

    sht30_init(&sht30, I2C_PORT, SCL_PIN, SDA_PIN, SHT30_ADDRESS_DEF, I2C_SPEED, MAX_WAIT_TIME);
    sht30_heater_control(&sht30, Heater_Disable);

    sht30_read_status_register(&sht30);

    int counter = 0;

    float temperature;
    float humidity;

    while(1){
        counter++;
        if(counter > startHeater){
            counter = 0;
            ESP_LOGI(TAG, "Starting heater.");
            sht30_heater_control(&sht30, Heater_Enable);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            sht30_read_status_register(&sht30);
        }

        sht30_single_shot(&sht30, Repeatability_High, ClockStretching_Enable);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        temperature = sht30_read_temperature_celsius(&sht30);
        humidity = sht30_read_humidity(&sht30);
        ESP_LOGI(TAG, "Temperature is %.2f celsius", temperature);
        ESP_LOGI(TAG, "Humidity is %.2f", humidity);
    }

}
