#include "../include/ram.h"
#include "../include/opcodes.h"
#include "../include/registers_flags.h"
#include "../include/instructions.h"
#include "../include/instructions_helpers.h"

int execute(uint8_t *ram, uint32_t sp_value)
{
	struct registers regs;
	union flags flgs;
	uint16_t opc;
	uint32_t arg;
	int opc_size;
	int is_jmp;
	regs.pc = 0;
	regs.sp = sp_value;
	regs.bp = sp_value;
	while (1) {
		arg = 0;
		opc_size = OPC_SIZE;
		opc = read_ram_16(ram, regs.pc);
		if(arg_num(opc) == 1) {
			arg = read_ram_32(ram, regs.pc + OPC_SIZE);
			opc_size += arg_num(opc) * ARG_SIZE;
		}
		is_jmp = functions[opc](ram, &regs, &flgs, arg);
		if(is_jmp != EXEC_JMP) 
			regs.pc += opc_size;
		if(is_jmp == EXEC_HALT) 
			break;
	}
	return 0;
}