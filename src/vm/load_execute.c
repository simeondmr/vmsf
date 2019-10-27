#include "../include/load_execute.h"
#include "../include/ram.h"
#include "../include/rom_loader.h"
#include "../include/vm.h"

uint32_t load_execute(char *filename)
{
	uint8_t *ram = setup_ram();
	uint32_t sp_value = rom_loader(ram, filename);
	if (!sp_value) {
		unsetup_ram(ram);
		return 0;
	}
	execute(ram, sp_value);
	unsetup_ram(ram);
	return 1;
}