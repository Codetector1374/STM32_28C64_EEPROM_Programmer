//
// Created by Codetector on 1/5/19.
//
#include <stdlib.h>
#include "74hc595.h"
#include "stm32f1xx_hal.h"
#include "dwt_stm32_delay.h"

sr595* sr595_create(GPIO_TypeDef *dataGPIO, uint16_t dataPin,
                    GPIO_TypeDef* latchGPIO, uint16_t latchPin,
                    GPIO_TypeDef* clockGPIO, uint16_t clockPin,
                    uint8_t registerCount) {
    sr595* sr = calloc(sizeof(sr595), 1);

    if (sr != NULL) {

        sr->registerCount = registerCount;

        sr->dataGPIO = dataGPIO;
        sr->dataPin = dataPin;

        sr->latchGPIO = latchGPIO;
        sr->latchPin = latchPin;

        sr->clockGPIO = clockGPIO;
        sr->clockPin = clockPin;

        sr->chipData = calloc(sizeof(uint16_t), registerCount);
        if (sr->chipData == NULL) {
            free(sr);
            return NULL;
        }
        return sr;
    }
    return NULL;
}

void shiftOut(sr595* sr) {

}

void latch(sr595* sr) {

}

uint8_t sr595_get_bit(sr595 *sr, uint16_t bit) {
    uint8_t chipCount = (uint8_t) (bit / 8);
    uint8_t bitCount = (uint8_t) (bit % 8);
    if (chipCount < sr->registerCount) {
        return (uint8_t) ((sr->chipData[chipCount] >> bitCount) & 1);
    }
    return 0xFF;
}

void sr595_mod_bit(sr595 *sr, uint16_t bit, uint8_t data) {
    uint8_t chipCount = (uint8_t) (bit / 8);
    uint8_t bitCount = (uint8_t) (bit % 8);
    if (chipCount < sr->registerCount) {
        if (data) {
            sr->chipData[chipCount] |= ((uint8_t)1 << bitCount);
        } else {
            sr->chipData[chipCount] &= ~((uint8_t)1 << bitCount);
        }
    }
}

uint8_t sr595_chip_data_get(sr595 *sr, uint8_t chipId) {
    if (chipId < sr->registerCount) {
        return *(sr->chipData + chipId);
    }
}

void sr595_chip_data_set(sr595 *sr, uint8_t chipId, uint8_t chipData) {
    if (chipId < sr->registerCount) {
        *(sr->chipData + chipId) = chipData;
    }
}