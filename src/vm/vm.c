#include <stdio.h>
#include "../include/opcodes.h"
#include "../include/registers_flags.h"
#include "../include/instructions.h"
#include "../include/ram.h"

extern void (*functions[256]) (uint8_t *ram, struct registers *regs, union flags *flgs); 

enum opcodes fetch(uint8_t *ram, uint32_t *pc) 
{
	unsigned short int code = ram[*pc] << 4;
	(*pc)++;
	return code |= ram[*pc];
}

int execute(uint8_t *ram) 
{
  struct registers regs;
  union flags flgs;
  uint8_t *memory = setup_ram();
  
  while (1) {
    functions[fetch(memory, &regs.pc)](memory, &regs, &flgs);
  }
    
}
