#ifndef __ROM_LOADER_H
#define __ROM_LOADER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t rom_loader(uint8_t *ram, char *filename);

#endif