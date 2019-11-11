#include <stdio.h>
#include "../include/vm/ram.h"
#include "../include/vm/registers_flags.h"
#include "../include/vm/opcodes.h"
#include "../include/vm/instructions.h"
#include "../include/vm/instructions_helpers.h"

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
	regs->sp -= 4;
	uint32_t pop_value = read_ram_32(ram, regs->sp);
	return pop_value;
}

void push_32(uint8_t *ram, struct registers *regs, uint32_t value) 
{
	write_ram_32(ram, regs->sp, value);
	regs->sp += 4;
}

int is_negative(uint32_t value) 
{
	return (value & 1<<31) ? 1 : 0;
}

uint32_t abs(uint32_t value) 
{
	return is_negative(value) ? -value : value;
}

uint32_t abs2(uint32_t value) 
{
	return value & (~(1<<31));
}

uint32_t calc_sum(uint32_t a, uint32_t b, int carry, int neg) 
{
	if (neg) {
		b = ~b;
		carry = !carry;
	}
	return a + b + carry;
}

int is_overflow(uint32_t a, uint32_t b, int carry, int neg) 
{
	if(neg) {
		b = ~b;
		carry = !carry;
	}
	uint32_t s = calc_sum(a, b, carry, 0);
	return (!is_negative(a) && !is_negative(b) && is_negative(s)) || (is_negative(a) && is_negative(b) && !is_negative(s));
}

int is_subcarry(uint32_t a, uint32_t b, int carry, int neg) 
{
	if(neg) {
		b = ~b;
		carry = !carry;
	}
	uint32_t s = calc_sum(abs2(a), abs2(b), carry, 0);
	return is_negative(s) ^ neg;
}

int is_carry(uint32_t a, uint32_t b, int carry, int neg) 
{
	return is_overflow(a, b, carry, neg) ^ is_subcarry(a, b, carry, neg);
}

void set_flags(union flags *flgs, uint32_t value) 
{
	flgs->zero = value == 0;
	flgs->negative = is_negative(value);
	flgs->overflow = 0;
	flgs->carry = 0;
}

void set_flags_add_sub(union flags *flgs, uint32_t a, uint32_t b, int carry, int neg)
{
	uint32_t r = calc_sum(a, b, carry, neg);
	set_flags(flgs, r);
	flgs->overflow = is_overflow(a, b, r, neg);
	flgs->carry = is_carry(a, b, carry, neg);
}

void push_32_set_flags(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t value)
{
	push_32(ram, regs, value);
	set_flags(flgs, value);
}

void push_32_add_sub(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t a, uint32_t b, int carry, int neg)
{
	uint32_t value = calc_sum(a, b, carry, neg);
	push_32(ram, regs, value);
	set_flags_add_sub(flgs, a, b, carry, neg);
}

int isjump(uint16_t op) 
{
	if (op == JMP
	  || op == JMPEQ 
	  || op == JMPLT
	  || op == JMPGT
	  || op == JMPLE
	  || op == JMPGE
	  || op == JMPAB
	  || op == JMPBL
	  || op == JMPAE
	  || op == JMPBE
	  || op == JMPNE
	  || op == CALL
	  || op == RET
	  || op == POPALL) 
	{
	  return 1;
	}
	return 0;
}

int arg_num(uint16_t op) 
{
	if (isjump(op) || op == PUSH || op == INT || op == OUT || op == IN) {
		if (op == POPALL)
			return 0;
		return 1;
	}
	return 0;
}