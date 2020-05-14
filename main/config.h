#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//FREERTOS
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
//system
#include "esp_err.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
//driver
#include "driver/gpio.h"


/* clang-format off */
#define B_BOX_VERSION    2
//Pin definition for B-Box
#define POWER_HOLD_PIN   21 //OUTPUT
#if(B_BOX_VERSION == 2)
#define POWER_DETECT_PIN 20 //INPUT PULLUP ISR(GPIO_PIN_INTR_LOLEVEL) 
#else
#define POWER_DETECT_PIN 33 //INPUT PULLUP ISR(GPIO_PIN_INTR_LOLEVEL) 
#endif

#define BUTTON_1_PIN     35 //INPUT PULLUP
#define BUTTON_2_PIN     1  //INPUT PULLUP
#define BUTTON_3_PIN     0  //INPUT PULLUP

#define BUZZER_PIN       2  //PWM
#define RUN_LEN_PIN      3  //OUTPUT

#if(B_BOX_VERSION == 2)
#define BATTERY_ADC_PIN  19 //ADC
#else
#define BATTERY_ADC_PIN  6 //ADC
#endif

#define LCD_RESET_PIN    14 //OUTPUT
#define LCD_MOSI_PIN     13 //SPI master
#define LCD_SCLK_PIN     12 //SPI master
#define LCD_CS_PIN       11 //SPI master
#define LCD_DC_PIN       10 //OUTPUT
#define LCD_BL_PIN       4  //OUTPUT

#define MPU_SDA_PIN      9  //I2C
#define MPU_SCL_PIN      8  //I2C
#define MPU_INT_PIN      7  //INPUT ISR(?)

#define MIC_SCK_PIN      36 //I2S
#define MIC_WS_PIN       38 //I2S
#define MIC_SDOUT_PIN    37 //I2S

#define B_BOX_GPIO_INPUT_SEL ( (1ULL << POWER_DETECT_PIN) | (1ULL << BUTTON_1_PIN) | (1ULL << BUTTON_2_PIN) \
                              | ((1ULL << BUTTON_3_PIN)) | (1ULL << MPU_INT_PIN) )

#define B_BOX_GPIO_OUTPUT_SEL ( (1ULL << POWER_HOLD_PIN) | (1ULL << RUN_LEN_PIN) | (1ULL << LCD_RESET_PIN) \
                              | ((1ULL << LCD_DC_PIN)) | (1ULL << LCD_BL_PIN) )                              
/* clang-format on */


#endif /* __CONFIG_H_ */