#ifndef SHT30_H_
#define SHT30_H_

#include <stdint.h>
#include <stdlib.h>
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

static const char *TAG_SHT30 = "SHT30";

#define SHT30_ADDRESS_DEF           0x44
#define SHT30_ADDRESS_B             0x45     
#define MAX_WAIT_TIME               0xFFFFFFFF     

typedef enum {

    SingleShot_CS               = 0x2C,
    SingleShot_DCS              = 0x24,

    SingleShot_RH_CS            = 0x06,
    SingleShot_RM_CS            = 0x0D,
    SingleShot_RL_CS            = 0x10,

    SingleShot_RH_DCS           = 0x00,
    SingleShot_RM_DCS           = 0x0B,
    SingleShot_RL_DCS           = 0x16,


    Periodic_05                 = 0x20,
    Periodic_1                  = 0x21,
    Periodic_2                  = 0x22,
    Periodic_4                  = 0x23,
    Periodic_10                 = 0x10,

    Periodic_RH_05              = 0x32,
    Periodic_RM_05              = 0x24,
    Periodic_RL_05              = 0x2F,

    Periodic_RH_1               = 0x30,
    Periodic_RM_1               = 0x26,
    Periodic_RL_1               = 0x2D,

    Periodic_RH_2               = 0x36,
    Periodic_RM_2               = 0x20,
    Periodic_RL_2               = 0x2B,

    Periodic_RH_4               = 0x34,
    Periodic_RM_4               = 0x22,
    Periodic_RL_4               = 0x29,

    Periodic_RH_10              = 0x37,
    Periodic_RM_10              = 0x21,
    Periodic_RL_10              = 0x2A,

    FetchCommand                = 0xE000,
    ARTCommand                  = 0x2B32,
    BreakCommand                = 0x3093,

    SoftResetCommand            = 0x30A2,

    Heater                      = 0x30,
    HeaterEnable                = 0x6D,
    HeaterDisable               = 0x66,

    StatusRegister              = 0xF32D,
    ClrStatusRegister           = 0x3041,

    CommandLength               = 2,

}sht30_command_t;

typedef enum {

    Repeatability_High    = 1,
    Repeatability_Medium  = 2,
    Repeatability_Low     = 3,

}sht30_repeatability_t;

typedef enum {

    ClockStretching_Disable     = 0,
    ClockStretching_Enable      = 1,

}sht30_clock_stretching_t;

typedef enum {

    MPS_05      = 0,
    MPS_1       = 1,
    MPS_2       = 2,
    MPS_4       = 3,
    MPS_10      = 4,

}sht30_measurements_per_seconds_t;

typedef enum {

    Heater_Disable     = 0,
    Heater_Enable      = 1,

}sht30_heater_t;

typedef enum {

    ok,
    crc_error,
    data_not_ready,
    data_not_valid,
    error

}sht30_status_t;

typedef struct {

    uint16_t humidity;
    uint16_t temperature;

}sht30_t;

sht30_status_t sht30_init(sht30_t *sht30, uint8_t _i2c_port, uint8_t _scl_io_num, uint8_t _sda_io_num,
                        uint8_t _device_address, uint16_t _scl_speed_hz, uint32_t _scl_wait_us);
sht30_status_t sht30_single_shot(sht30_t *sht30, sht30_repeatability_t repeatability, sht30_clock_stretching_t clock);
sht30_status_t sht30_periodic(sht30_t *sht30, sht30_repeatability_t repeatability, sht30_measurements_per_seconds_t mps);
sht30_status_t sht30_fetch_data(sht30_t *sht30);
sht30_status_t sht30_art(sht30_t *sht30);
sht30_status_t sht30_break(sht30_t *sht30);
sht30_status_t sht30_soft_reset(sht30_t *sht30);
sht30_status_t sht30_heater_control(sht30_t *sht30, sht30_heater_t control);
sht30_status_t sht30_read_status_register(sht30_t *sht30);
sht30_status_t sht30_clear_status_register(sht30_t *sht30);

sht30_status_t sht30_write(sht30_t *sht30, uint8_t *command);
sht30_status_t sht30_read(sht30_t *sht30, uint8_t *dataRec, size_t len);
uint8_t sht30_calculate_crc(sht30_t *sht30, uint8_t *data);

float sht30_read_temperature_celsius(sht30_t *sht30);
float sht30_read_temperature_fahreinheit(sht30_t *sht30);
float sht30_read_humidity(sht30_t *sht30);


#endif