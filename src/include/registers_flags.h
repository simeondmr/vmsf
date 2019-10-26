#ifndef __REGISTERS_FLAGS_H
#define __REGISTERS_FLAGS_H
#include <stdint.h>

struct registers {
	uint32_t pc;
	int32_t sp;
	uint32_t bp;
};

union flags {
	uint8_t f_data;
	struct {
		uint8_t overflow : 1;
		uint8_t carry : 1;
		uint8_t zero : 1;
		uint8_t negative : 1;
		uint8_t flag_4 : 1;
		uint8_t flag_5 : 1;
		uint8_t flag_6 : 1;
		uint8_t flag_7 : 1;
	};
};
#endif