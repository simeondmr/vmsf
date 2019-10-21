#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SIZE 0x10000

uint8_t *setup_ram() {
	uint8_t *ram = calloc(MAX_SIZE, sizeof(uint8_t));
}

void unsetup_ram(uint8_t *ram) {
	free(ram);
}

void write_ram(uint8_t *ram, uint32_t addr, uint8_t *data, uint32_t size) {
	for(uint32_t i = 0; i < size && addr + i < MAX_SIZE; i++) {
		ram[addr + i] = data[i];
	}
}

void read_ram(uint8_t *ram, uint32_t addr, uint8_t *data, uint32_t size) {
	for(uint32_t i = 0; i < size && addr + i < MAX_SIZE; i++) {
		data[i] = ram[addr + i];
	}
}

#define WRITE_READ_RAM_X(size)                                                \
void write_ram_##size(uint8_t *ram, uint32_t addr, uint##size##_t data) {     \
	write_ram(ram, addr, (uint8_t*) &data, size/8);                             \
}                                                                             \
                                                                              \
uint##size##_t read_ram_##size(uint8_t *ram, uint32_t addr) {                 \
	uint##size##_t data;                                                        \
	read_ram(ram, addr, (uint8_t*) &data, size/8);                              \
	return data;                                                                \
}

WRITE_READ_RAM_X(8)
WRITE_READ_RAM_X(16)
WRITE_READ_RAM_X(32)
