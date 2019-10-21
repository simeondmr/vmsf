#include <stdio.h>
#include "../include/registers_flags.h"

void nop(uint8_t *ram, struct registers *regs, union flags *flgs)
{
	
}

void (*functions[256]) (uint8_t *ram, struct registers *regs, union flags *flgs) = {
  nop
};

