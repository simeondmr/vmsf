#ifndef __RAM_H
#define __RAM_H

uint8_t *setup_ram();
void unsetup_ram(uint8_t *ram);
void write_ram(uint8_t *ram, uint32_t addr, uint8_t *data, uint32_t size);
void read_ram(uint8_t *ram, uint32_t addr, uint8_t *data, uint32_t size);
#define WRITE_READ_RAM_X(size)                                                \
void write_ram_##size(uint8_t *ram, uint32_t addr, uint##size##_t data);      \
uint##size##_t read_ram_##size(uint8_t *ram, uint32_t addr);
WRITE_READ_RAM_X(8)
WRITE_READ_RAM_X(16)
WRITE_READ_RAM_X(32)
#undef WRITE_READ_RAM_X

#endif