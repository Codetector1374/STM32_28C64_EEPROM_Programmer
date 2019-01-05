//
// Created by Codetector on 1/5/19.
//

#ifndef INC_28C64PROGRAMMER_74HC595_H
#define INC_28C64PROGRAMMER_74HC595_H

#include "gpio.h"

typedef struct sr595 {
    uint8_t registerCount;

    GPIO_TypeDef *dataGPIO;
    uint16_t dataPin;

    GPIO_TypeDef *latchGPIO;
    uint16_t latchPin;

    GPIO_TypeDef *clockGPIO;
    uint16_t clockPin;

    uint8_t *chipData;
} sr595;

sr595* sr595_create(GPIO_TypeDef *dataGPIO, uint16_t dataPin,
        GPIO_TypeDef* latchGPIO, uint16_t latchPin,
        GPIO_TypeDef* clockGPIO, uint16_t clockPin,
        uint8_t registerCount);

uint8_t sr595_get_bit(sr595 *sr, uint16_t bit);
void sr595_mod_bit(sr595 *sr, uint16_t bit, uint8_t data);

uint8_t sr595_chip_data_get(sr595 *sr, uint8_t chipId);
void sr595_chip_data_set(sr595 *sr, uint8_t chipId, uint8_t chipData);

void sr595_shiftOut(sr595* sr);
void sr595_latch(sr595* sr);

#endif //INC_28C64PROGRAMMER_74HC595_H
