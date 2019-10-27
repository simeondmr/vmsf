#include <stdio.h>
#include "../include/ram.h"
#include "../include/registers_flags.h"
#include "../include/opcodes.h"
#include "../include/instructions_helpers.h"
#include "../include/instructions.h"

int execute_nop(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	return EXEC_OK;
}

int execute_push(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	push_32_set_flags(ram, regs, flgs, arg);
	return EXEC_OK;
}

int execute_add(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32_add_sub(ram, regs, flgs, param1, param2, 0, 0);
	return EXEC_OK;
}

int execute_sub(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32_add_sub(ram, regs, flgs, param1, param2, 0, 1);
	return EXEC_OK;
}

int execute_mul(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32_set_flags(ram, regs, flgs, param1 * param2);
	return EXEC_OK;
}

int execute_div(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	uint32_t r = 0;
	if (param2 != 0) {
		r = param1 / param2;
	}
	push_32_set_flags(ram, regs, flgs, r);
	flgs->overflow = param2 == 0;
	return EXEC_OK;
}

int execute_addc(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32_add_sub(ram, regs, flgs, param1, param2, 0, 0);
	return EXEC_OK;
}

int execute_subc(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32_add_sub(ram, regs, flgs, param1, param2, flgs->carry, 1);
	return EXEC_OK;
}

int execute_inc(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param = pop_32(ram, regs);
	push_32_add_sub(ram, regs, flgs, param, 1, 0, 0);
	return EXEC_OK;
}

int execute_dec(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param = pop_32(ram, regs);
	push_32_add_sub(ram, regs, flgs, param, 1, 0, 1);
	return EXEC_OK;
}

int execute_swap(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32(ram, regs, param1);
	push_32(ram, regs, param2);
	return EXEC_OK;
}

int execute_xor(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32_set_flags(ram, regs, flgs, param1^param2);
	return EXEC_OK;
}

int execute_and(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32_set_flags(ram, regs, flgs, param1&param2);
	return EXEC_OK;
}

int execute_or(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	push_32_set_flags(ram, regs, flgs, param1|param2);
	return EXEC_OK;
}

int execute_not(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param = pop_32(ram, regs);
	push_32_set_flags(ram, regs, flgs, ~param);
	return EXEC_OK;
}

int execute_call(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	// to implement
	return EXEC_OK;
}

int execute_pushpc(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	push_32(ram, regs, regs->pc);
	return EXEC_OK;
}

int execute_jmp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	regs->pc = arg;
	return EXEC_JMP;
}

int execute_ret(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	// to implement
	return EXEC_OK;
}

int execute_ref(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) // TODO: implement security (access only if a>=bp?)
{
	uint32_t param = pop_32(ram, regs);
	param = read_ram_32(ram, param);
	push_32_set_flags(ram, regs, flgs, param);
	return EXEC_OK;
}

int execute_dup(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t value = read_ram_32(ram, regs->sp - 3);
	push_32(ram, regs, value);
	return EXEC_OK;
}

int execute_mod(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	uint32_t r = 0;
	if (param2 != 0) {
		r = param1 % param2;
	}
	push_32_set_flags(ram, regs, flgs, r);
	flgs->overflow = param2 == 0;
	return EXEC_OK;
}

int execute_cmp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	set_flags_add_sub(flgs, param1, param2, 0, 1);
	return EXEC_OK;
}

int execute_jmpeq(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (flgs->zero) {
		regs->pc = arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmplt(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (flgs->negative) {
		regs->pc = arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpgt(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (flgs->negative == flgs->overflow && !flgs->zero) {
		regs->pc = arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmple(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (flgs-> negative || flgs->zero) {
		regs->pc = arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpge(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (flgs->negative == flgs->overflow || flgs->zero) {
		regs->pc = arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpab(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (!flgs->carry && !flgs->zero) {
	  regs->pc = arg;
	  return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpbl(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (flgs->carry) {
		regs->pc = arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpae(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (!flgs->carry && flgs->zero) {
		regs->pc = arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpbe(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (flgs->carry || flgs->zero) {
		regs->pc=arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpne(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	if (!flgs->zero) {
		regs->pc=arg;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_divmod(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param2 = pop_32(ram, regs);
	uint32_t param1 = pop_32(ram, regs);
	uint32_t rd=0;
	uint32_t rm=0;
	if (param2 != 0) {
		rd = param1 / param2;
		rm = param1 % param2;
	}
	push_32_set_flags(ram, regs, flgs, rd);
	push_32_set_flags(ram, regs, flgs, rm);
	flgs->overflow = param2 == 0;
	return EXEC_OK;
}

int execute_addsp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param = pop_32(ram, regs);
	regs->sp += param;
	return EXEC_OK;
}

int execute_subsp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	uint32_t param = pop_32(ram, regs);
	regs->sp -= param;
	return EXEC_OK;
}

int execute_incsp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	regs->sp++;
	return EXEC_OK;
}

int execute_decsp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	regs->sp--;
	return EXEC_OK;
}

int execute_unref(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	// to implement
	return EXEC_OK;
}

int execute_pushbp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	push_32(ram, regs, regs->bp);
	return EXEC_OK;
}

int execute_popbp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	regs->bp = pop_32(ram, regs);
	return EXEC_OK;
}

int execute_pushall(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	push_32(ram, regs, regs->pc);
	push_8(ram, regs, flgs->f_data);
	push_32(ram, regs, regs->bp);
	push_32(ram, regs, regs->sp);
	return EXEC_OK;
}

int execute_popall(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	regs->sp = pop_32(ram, regs);
	regs->bp = pop_32(ram, regs);
	flgs->f_data = pop_8(ram, regs);
	regs-> pc = pop_32(ram, regs);
	return EXEC_OK;
}

int execute_halt(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	return EXEC_HALT;
}

int execute_pushflags(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	push_8(ram, regs, flgs->f_data);
	return EXEC_OK;
}

int execute_popflags(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) 
{
	flgs->f_data = pop_8(ram, regs);
	return EXEC_OK;
}

execute_opcode *functions[256] = {
	execute_nop,
	execute_push,
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_addc,
	execute_subc,
	execute_inc,
	execute_dec,
	execute_swap,
	execute_xor,
	execute_and,
	execute_or,
	execute_not,
	execute_call,
	execute_pushpc,
	execute_jmp,
	execute_ret,
	execute_ref,
	execute_dup,
	execute_mod,
	execute_cmp,
	execute_jmpeq,
	execute_jmplt,
	execute_jmpgt,
	execute_jmple,
	execute_jmpge,
	execute_jmpab,
	execute_jmpbl,
	execute_jmpae,
	execute_jmpbe,
	execute_jmpne,
	execute_divmod,
	execute_addsp,
	execute_subsp,
	execute_incsp,
	execute_decsp,
	execute_unref,
	execute_pushbp,
	execute_popbp,
	execute_pushall,
	execute_popall,
	execute_halt,
	execute_pushflags,
	execute_popflags
};