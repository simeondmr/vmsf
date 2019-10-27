#include "../include/rom_loader.h"
#include "../include/ram.h"

uint32_t rom_loader(uint8_t *ram, char *filename)
{
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		return 0;
	}
	uint32_t sp = 0;
	sp = fread(ram, 1, MAX_SIZE, fp);
	fclose(fp);
	return sp;
}