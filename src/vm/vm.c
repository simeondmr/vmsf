#include <stdio.h>
#include "../include/ram.h"
#include "../include/opcodes.h"
#include "../include/registers_flags.h"
#include "../include/instructions.h"

//extern void (*functions[256]) (uint8_t *ram, struct registers *regs, union flags *flgs); 

int execute(uint8_t *ram) 
{
	struct registers regs;
	union flags flgs;
	uint8_t *memory = setup_ram();
	uint16_t op;
	uint32_t arg;
	int opsize;
	int is_jmp;
	
	while (1) {
		op = read_ram_16(memory, regs.pc);
		arg = 0;
		opsize = 2;
		if(op == PUSH) {
			arg = read_ram_32(memory, regs.pc+2);
			opsize = 6;
		}
		is_jmp = functions[op](memory, &regs, &flgs, arg);
		if(is_jmp == EXEC_JMP) {
			regs.pc += opsize;
		}
		if(is_jmp == EXEC_HALT) {
			break;
		}
	}
	return 0;	
}

int main()
{
	//execute(NULL);
	return 0;
}