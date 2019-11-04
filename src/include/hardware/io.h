#ifndef __IO_H
#define __IO_H
#include <stdint.h>
#include "../vm/registers_flags.h"
#include "../hardware/console.h"

typedef int (interrupt)(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg);

interrupt *int_table[] = {
	int_printchar
};


#endif