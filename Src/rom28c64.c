//
// Created by codetector on 19-1-6.
//
#include "rom28c64.h"
#include <stdlib.h>
void rom28c64_write_chip_state(rom28c64 *rom, uint8_t ce, uint8_t oe,
                               uint8_t we, uint16_t addr,uint8_t data, uint8_t outEn);

rom28c64* rom28c64_create(GPIO_TypeDef* ioCtrlGPIO, uint16_t ioCtrlPin,sr595 *out) {
    rom28c64* rom = calloc(sizeof(rom28c64), 1);

    if (rom == NULL) {
        return NULL;
    }

    rom->ioCtrlGPIO= ioCtrlGPIO;
    rom->ioCtrlPin = ioCtrlPin;
    HAL_GPIO_WritePin(rom->ioCtrlGPIO, rom->ioCtrlPin, GPIO_PIN_SET); // Disable last output.
    rom->out = out;

    return rom;
}

void rom28c64_write_address(rom28c64 *rom, uint16_t address, uint8_t data) {
    address &= 0b0001111111111111;
    rom28c64_write_chip_state(rom, 0, 1, 1, address, data, 0); // Chip En, Out Dis
    rom28c64_write_chip_state(rom, 0, 1, 1, address, data, 1); // Write Data to IO
    rom28c64_write_chip_state(rom, 0, 1, 0, address, data, 1); // Pull Write
    rom28c64_write_chip_state(rom, 0, 1, 1, address, data, 0); // Reset Write, data off
}

void rom28c64_write_chip_state(rom28c64 *rom, uint8_t ce, uint8_t oe,
        uint8_t we, uint16_t addr,uint8_t data, uint8_t outEn) {
    uint8_t r0Data = 0, r1Data = 0;
    r0Data = (uint8_t) addr;
    sr595_chip_data_set(rom->out, 0, r0Data); // Set Data SRegister 0

    r1Data = (uint8_t) ((uint8_t)(addr >> 8) & 0b00011111);
    r1Data |= ((ce & 0b1) | (oe & 0b1) << 1 | (we & 0b1) << 2) << 5;
    sr595_chip_data_set(rom->out, 1, r1Data); // Set Data SRegister 1
    sr595_shiftOut(rom->out);
    sr595_latch(rom->out);

    if (outEn) {
        sr595_chip_data_set(rom->out, 2, data);
        sr595_shiftOut(rom->out);
        sr595_latch(rom->out);
        HAL_GPIO_WritePin(rom->ioCtrlGPIO, rom->ioCtrlPin, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(rom->ioCtrlGPIO, rom->ioCtrlPin, GPIO_PIN_SET);
    }

}