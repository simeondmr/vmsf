#ifndef __REGISTERS_FLAGS_H
#define __REGISTERS_FLAGS_H
struct registers {
	int pc;
	int sp;
	int bp;
};

union flags {
	unsigned char f_data;
	struct {
		unsigned char overflow : 1;
		unsigned char carry : 1;
		unsigned char zero : 1;
		unsigned char negative : 1;
		unsigned char flag_4 : 1;
		unsigned char flag_5 : 1;
		unsigned char flag_6 : 1;
		unsigned char flag_7 : 1;
	};
};
#endif