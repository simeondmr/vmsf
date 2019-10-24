#include <stdio.h>
#include "../include/ram.h"
#include "../include/registers_flags.h"
#include "../include/opcodes.h"
#include "../include/instructions_helpers.h"
#include "../include/instructions.h"

int execute_nop(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	return EXEC_OK;
}

int execute_push(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	push_32_set_flags(ram, regs, flgs, arg);
	return EXEC_OK;
}

int execute_add(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_sub(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs), b=pop_32(ram, regs);
	push_32_set_flags2(ram, regs, flgs, a, b, 0, 1);
	return EXEC_OK;
}

int execute_mul(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_div(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs), b=pop_32(ram, regs), r=0;
	if(b!=0) {
		r=a/b;
	}
	push_32_set_flags(ram, regs, flgs, r);
	flgs->overflow = b==0;
	return EXEC_OK;
}

int execute_addc(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_subc(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs), b=pop_32(ram, regs);
	push_32_set_flags2(ram, regs, flgs, a, b, flgs->carry, 1);
	return EXEC_OK;
}

int execute_inc(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_dec(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs);
	push_32_set_flags2(ram, regs, flgs, a, 1, 0, 1);
	return EXEC_OK;
}

int execute_swap(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_xor(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs), b=pop_32(ram, regs);
	push_32_set_flags(ram, regs, flgs, a^b);
	return EXEC_OK;
}

int execute_and(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_or(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs), b=pop_32(ram, regs);
	push_32_set_flags(ram, regs, flgs, a|b);
	return EXEC_OK;
}

int execute_not(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_call(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_pushpc(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_jmp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs);
	regs->pc=a;
	return EXEC_JMP;
}

int execute_ret(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_ref(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) { // todo: implement security (access only if a>=bp?)
	uint32_t a=pop_32(ram, regs);
	a=read_ram_32(ram, a);
	push_32_set_flags(ram, regs, flgs, a);
	return EXEC_OK;
}

int execute_dup(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_mod(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs), b=pop_32(ram, regs), r=0;
	if(b!=0) {
		r=a%b;
	}
	push_32_set_flags(ram, regs, flgs, r);
	flgs->overflow = b==0;
	return EXEC_OK;
}

int execute_cmp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_jmpeq(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) { // todo: pop or peek?
	uint32_t a=pop_32(ram, regs);
	if(flgs->zero)
	{
		regs->pc=a;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmplt(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_jmpgt(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs);
	if(flgs->negative == flgs->overflow && !flgs->zero)
	{
		regs->pc=a;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmple(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_jmpge(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs);
	if(flgs->negative == flgs->overflow || flgs->zero)
	{
		regs->pc=a;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpab(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_jmpbl(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs);
	if(flgs->carry)
	{
		regs->pc=a;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpae(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_jmpbe(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs);
	if(flgs->carry || flgs->zero)
	{
		regs->pc=a;
		return EXEC_JMP;
	}
	return EXEC_OK;
}

int execute_jmpne(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_divmod(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs), b=pop_32(ram, regs), rd=0, rm=0;
	if(b!=0) {
		rd=a/b;
		rm=a%b;
	}
	push_32_set_flags(ram, regs, flgs, rd);
	push_32_set_flags(ram, regs, flgs, rm);
	flgs->overflow = b==0;
	return EXEC_OK;
}

int execute_addsp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_subsp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	uint32_t a=pop_32(ram, regs);
	regs->sp -= a;
	return EXEC_OK;
}

int execute_incsp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_decsp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	regs->sp--;
	return EXEC_OK;
}

int execute_unref(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_pushbp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	push_32(ram, regs, regs->bp);
	return EXEC_OK;
}

int execute_popbp(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_pushall(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	push_32(ram, regs, regs->pc);
	push_8(ram, regs, flgs->f_data);
	push_32(ram, regs, regs->bp);
	push_32(ram, regs, regs->sp);
	return EXEC_OK;
}

int execute_popall(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_halt(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	return EXEC_HALT;
}

int execute_pushflags(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
	// to implement
	return EXEC_OK;
}

int execute_popflags(uint8_t *ram, struct registers *regs, union flags *flgs, uint32_t arg) {
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