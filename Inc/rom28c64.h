//
// Created by codetector on 19-1-6.
//

#ifndef INC_28C64PROGRAMMER_ROM28C64_H
#define INC_28C64PROGRAMMER_ROM28C64_H

#include "gpio.h"
#include "74hc595.h"
#include "74hc165.h"

typedef struct rom28c64 {
    GPIO_TypeDef* ioCtrlGPIO;
    uint16_t ioCtrlPin;

    sr595 *out;
    sr165 *in;
} rom28c64;

rom28c64* rom28c64_create(GPIO_TypeDef* ioCtrlGPIO, uint16_t ioCtrlPin,sr595 *out, sr165* in);

void rom28c64_write_address(rom28c64 *rom, uint16_t address, uint8_t data);
uint8_t rom28c64_read_address(rom28c64* rom, uint16_t address);

#endif //INC_28C64PROGRAMMER_ROM28C64_H
INC_28C64PROGRAMMER_ROM28C64_H