#include <stdio.h>
#include "../include/registers_flags.h"
#include "../include/opcodes.h"
#include "../include/instructions.h"
#include "../include/instructions_helpers.h"

uint8_t pop_8(uint8_t *ram, struct registers *regs)
{
	uint8_t pop_value = read_ram_8(ram, regs->sp);
	regs->sp -= 1;
	return pop_value;
}

void push_8(uint8_t *ram, struct registers *regs, uint8_t value) 
{
	regs->sp += 1;
	write_ram_8(ram, regs->sp, value);
}

uint32_t pop_32(uint8_t *ram, struct registers *regs) 
{
	uint32_t pop_value = read_ram_32(ram, regs->sp);
	regs->sp -= 4;
	return pop_value;
}

void push_32(uint8_t *ram, struct registers *regs, uint32_t value) 
{
	regs->sp += 4;
	write_ram_32(ram, regs->sp, value);
}

int is_negative(uint32_t value) 
{
	return (value & 1<<31) ? 1 : 0;
}

uint32_t abs(uint32_t value) 
{
	return value & ~(1<<31);
}

uint32_t calc_sum(uint32_t a, uint32_t b, int carry, int neg) 
{
	if (neg) {
		b=  -b;
		carry = -carry;
	}
	return a + b + carry;
}

int is_overflow(uint32_t a, uint32_t b, int carry, int neg) 
{ // todo: check
	uint32_t r = calc_sum(a, b, carry, neg);
	return !(is_negative(a) ^ is_negative(b) ^ neg) && is_negative(r) ^ is_negative(a);
}

int is_subcarry(uint32_t a, uint32_t b, int carry, int neg) 
{ // todo: check
	a = abs(a);
	b = abs(b);
	if (neg) {
		b = -b;
		carry = -carry;
	}
	return is_negative(a + b + carry);
}

int is_carry(uint32_t a, uint32_t b, int carry, int neg) 
{ // todo: check
	uint32_t r = calc_sum(a, b, carry, neg);
	return is_overflow(a, b, r, neg) ^ is_subcarry(a, b, carry, neg);
}

void set_flags(union flags *flgs, uint32_t value) 
{
	flgs->zero = value == 0;
	flgs->negative = is_negative(value);
	flgs->overflow = 0;
	flgs->carry = 0;
}

void set_flags2(union flags *flgs, uint32_t a, uint32_t b, int carry, int neg)
{
	uint32_t r = calc_sum(a, b, carry, neg);
	set_flags(flgs, r);
	flgs->overflow = is_overflow(a, b, r, neg);
	flgs->carry = is_carry(a, b, r, carry, neg);
}

void push_32_set_flags(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t value)
{
	push_32(ram, regs, value);
	set_flags(flgs, value);
}

void push_32_set_flags2(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t a, uint32_t b, int carry, int neg)
{
	uint32_t value = calc_sum(a, b, carry, neg);
	push_32(ram, regs, value);
	set_flags2(flgs, a, b, carry, neg);
}