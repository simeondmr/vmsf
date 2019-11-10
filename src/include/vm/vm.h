#ifndef __VM_H
#define __VM_H
#include <stdint.h>
#include "../hardware/io.h"

int execute(uint8_t *ram, uint32_t sp_value, struct ports *prts);

#endif