#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

typedef int (execute_opcode)(uint8_t *ram, struct registers *regs, union flags*, uint32_t arg);

enum exec_result {
	EXEC_OK,
	EXEC_JMP,
	EXEC_HALT
};

#endif