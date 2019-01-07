//
// Created by codetector on 19-1-6.
//
#include "74hc165.h"
#include "dwt_stm32_delay.h"
#include <stdlib.h>

sr165* sr165_create(GPIO_TypeDef* ldGPIO, uint16_t ldPin,
                    GPIO_TypeDef* clkGPIO, uint16_t clkPin,
                    GPIO_TypeDef* dataGPIO, uint16_t dataPin) {
    sr165* sr = calloc(sizeof(sr), 1);
    if (sr == NULL) {
        return NULL;
    }
    sr->ldGPIO = ldGPIO;
    sr->ldPin = ldPin;

    sr->clkGPIO = clkGPIO;
    sr->clkPin = clkPin;

    sr->dataGPIO = dataGPIO;
    sr->dataPin = dataPin;

    HAL_GPIO_WritePin(sr->ldGPIO, sr->ldPin, GPIO_PIN_SET);

    return sr;
}
void sr165_load(sr165* sr) {
    HAL_GPIO_WritePin(sr->ldGPIO, sr->ldPin, GPIO_PIN_RESET);
    DWT_Delay_us(10);
//    HAL_GPIO_WritePin(sr->ldGPIO, sr->ldPin, GPIO_PIN_SET);
}
uint8_t sr165_read_one_byte(sr165* sr) {
    uint8_t data = 0U;
    for (int i = 7; i >= 0; i--) {
        data |= (uint8_t) (HAL_GPIO_ReadPin(sr->dataGPIO, sr->dataPin) == GPIO_PIN_SET) << i;
//        HAL_GPIO_WritePin(sr->clkGPIO, sr->clkPin, GPIO_PIN_SET);
//        DWT_Delay_us(10);
//        HAL_GPIO_WritePin(sr->clkGPIO, sr->clkPin, GPIO_PIN_RESET);
//        DWT_Delay_us(1);
    }
    return data;
}
