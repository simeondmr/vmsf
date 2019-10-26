#include <stdio.h>
#include "../include/instructions_helpers.h"
#include "../include/vm.h"

int main()
{

	/* uint8_t test[100];
	  test[0] = 0x00;
	  test[1] = 0x01;
	  
	  
	  struct registers regs;
	  union flags flgs;

	  regs.bp = 0;
	  regs.sp = -1;
	  
	  //write_ram_32(test, 0, 42);
	  functions[PUSH](test, &regs, &flgs, 10);
	  functions[PUSH](test, &regs, &flgs, 3);
	  functions[ADDSP](test, &regs, &flgs, 0);
	  printf("%u %d %u\n",regs.pc, regs.sp, regs.bp);
	  printf("%d %d %d\n", flgs.carry, flgs.negative, flgs.zero);
	  printf("%d\n", read_ram_32(test, 4));
	  return 0;*/
	  execute(NULL);

}