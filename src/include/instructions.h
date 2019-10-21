#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H
void (*functions[256]) (uint8_t *ram, struct registers *regs, union flags *flgs);
#endif