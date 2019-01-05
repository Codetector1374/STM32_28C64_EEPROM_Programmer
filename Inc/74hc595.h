//
// Created by Codetector on 1/5/19.
//

#ifndef INC_28C64PROGRAMMER_74HC595_H
#define INC_28C64PROGRAMMER_74HC595_H

#include "gpio.h"

typedef struct sr595 {
    u_int8_t registerCount;

    GPIO_TypeDef *dataGPIO;
    uint16_t dataPin;

    GPIO_TypeDef *latchGPIO;
    uint16_t latchPin;

    GPIO_TypeDef *clockGPIO;
    uint16_t clockPin;

} sr595;
#endif //INC_28C64PROGRAMMER_74HC595_H
