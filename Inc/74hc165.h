//
// Created by codetector on 19-1-6.
//

#ifndef INC_28C64PROGRAMMER_74HC165_H
#define INC_28C64PROGRAMMER_74HC165_H

#include "stm32f1xx_hal.h"

typedef struct sr165 {
    GPIO_TypeDef *ldGPIO;
    uint16_t ldPin;

    GPIO_TypeDef* clkGPIO;
    uint16_t clkPin;

    GPIO_TypeDef* dataGPIO;
    uint16_t dataPin;
} sr165;

sr165* sr165_create(GPIO_TypeDef* ldGPIO, uint16_t ldPin,
        GPIO_TypeDef* clkGPIO, uint16_t clkPin,
        GPIO_TypeDef* dataGPIO, uint16_t dataPin);
void sr165_load(sr165* sr);
uint8_t sr165_read_one_byte(sr165* sr);

#endif //INC_28C64PROGRAMMER_74HC165_H
