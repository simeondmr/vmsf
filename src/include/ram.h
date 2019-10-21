#ifndef __RAM_H
#define __RAM_H
uint8_t *setup_ram();
void unsetup_ram(uint8_t *ram);
void write_ram(uint8_t *ram, uint32_t addr, uint8_t *data, uint32_t size);
void read_ram(uint8_t *ram, uint32_t addr, uint8_t *data, uint32_t size);
#endif