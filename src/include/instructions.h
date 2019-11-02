#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

typedef int (execute_opcode)(uint8_t *ram, struct registers *regs, union flags*, uint32_t arg);

enum exec_result {
	EXEC_OK,
	EXEC_JMP,
	EXEC_HALT
};

execute_opcode execute_nop;
execute_opcode execute_push;
execute_opcode execute_add;
execute_opcode execute_sub;
execute_opcode execute_mul;
execute_opcode execute_div;
execute_opcode execute_addc;
execute_opcode execute_subc;
execute_opcode execute_inc;
execute_opcode execute_dec;
execute_opcode execute_swap;
execute_opcode execute_xor;
execute_opcode execute_and;
execute_opcode execute_or;
execute_opcode execute_not;
execute_opcode execute_call;
execute_opcode execute_pushpc;
execute_opcode execute_jmp;
execute_opcode execute_ret;
execute_opcode execute_ref;
execute_opcode execute_dup;
execute_opcode execute_mod;
execute_opcode execute_cmp;
execute_opcode execute_jmpeq;
execute_opcode execute_jmplt;
execute_opcode execute_jmpgt;
execute_opcode execute_jmple;
execute_opcode execute_jmpge;
execute_opcode execute_jmpab;
execute_opcode execute_jmpbl;
execute_opcode execute_jmpae;
execute_opcode execute_jmpbe;
execute_opcode execute_jmpne;
execute_opcode execute_divmod;
execute_opcode execute_addsp;
execute_opcode execute_subsp;
execute_opcode execute_incsp;
execute_opcode execute_decsp;
execute_opcode execute_unref;
execute_opcode execute_pushbp;
execute_opcode execute_popbp;
execute_opcode execute_pushall;
execute_opcode execute_popall;
execute_opcode execute_halt;
execute_opcode execute_pushflags;
execute_opcode execute_popflags;

#endif