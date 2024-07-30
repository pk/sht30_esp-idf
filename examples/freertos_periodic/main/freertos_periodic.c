#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "sht30.h"

#define SCL_PIN 8
#define SDA_PIN 9
#define I2C_PORT 0
#define I2C_SPEED 10000

static const char *TAG_ReadData = "ReadData";
static const char *TAG_PrintData = "PrintData";

sht30_t sht30;

void readData(void *parameter){

    sht30_init(&sht30, I2C_PORT, SCL_PIN, SDA_PIN, SHT30_ADDRESS_DEF, I2C_SPEED, MAX_WAIT_TIME);
    sht30_heater_control(&sht30, Heater_Disable);
    sht30_periodic(&sht30, Repeatability_High, MPS_05);

    vTaskDelay(1000 / 10);

    while(1){

        ESP_LOGI(TAG_ReadData, "Reading data...");
        sht30_fetch_data(&sht30);
        vTaskDelay(2000 / 10);

    }
    
}

void printData(void *parameter){

    float temp;

    while(1){

        temp = sht30_read_temperature_celsius(&sht30);

        ESP_LOGI(TAG_PrintData, "Printing data...");
        printf("Teplota je: %.2f\n", temp);
        vTaskDelay(500 / 10);
    }
}


void app_main(void)
{

    xTaskCreate(&readData, "ReadData", 4096, (void *)&sht30, 5, NULL);
    xTaskCreate(&printData, "PrintData", 2048, (void *)&sht30, 4, NULL);

}
