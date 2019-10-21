#ifndef __INSTRUCTIONS_HELPERS_H
#define __INSTRUCTIONS_HELPERS_H

uint8_t pop_8(uint8_t *ram, struct registers *regs);
void push_8(uint8_t *ram, struct registers *regs, uint8_t value);
uint32_t pop_32(uint8_t *ram, struct registers *regs);
void push_32(uint8_t *ram, struct registers *regs, uint32_t value);
int is_negative(uint32_t value);
uint32_t abs(uint32_t value);
uint32_t calc_sum(uint32_t a, uint32_t b, int carry, int neg);
int is_overflow(uint32_t a, uint32_t b, int carry, int neg);
int is_subcarry(uint32_t a, uint32_t b, int carry, int neg);
int is_carry(uint32_t a, uint32_t b, int carry, int neg);
void set_flags(union flags *flgs, uint32_t value);
void set_flags2(union flags *flgs, uint32_t a, uint32_t b, int carry, int neg);
void push_32_set_flags(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t value);
void push_32_set_flags2(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t a, uint32_t b, int carry, int neg);

#endif