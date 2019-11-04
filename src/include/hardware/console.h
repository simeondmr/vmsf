#ifndef __CONSOLE_H
#define __CONSOLE_H
#define PRINT_CHAR_PTR 0x00

int int_printchar(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg);

#endif