#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define CEIL_DIV(a,b) (((a)+(b)-1L)/(b))

#define VALUE_SIZE_BYTE 4L
#define BLOCK_SIZE_BYTE 16L
//#define RAM_SIZE_BYTE (256L)
//#define RAM_SIZE_BYTE (256L*256L)
//#define RAM_SIZE_BYTE (256L*256L*256L)
//#define RAM_SIZE_BYTE (256L*256L*256L*256L)
#define RAM_SIZE_BYTE (4L*1024*1024*1024)
#define TAB_SIZE_BYTE (RAM_SIZE_BYTE*VALUE_SIZE_BYTE/BLOCK_SIZE_BYTE-1L)
#define ALLOCABLE_SIZE_BYTE (RAM_SIZE_BYTE-TAB_SIZE_BYTE)
#define TAB_SIZE_VALUE (TAB_SIZE_BYTE/VALUE_SIZE_BYTE)
#define TAB_SIZE_BLOCK (TAB_SIZE_BYTE/BLOCK_SIZE_BYTE)
#define ALLOCABLE_SIZE_VALUE (ALLOCABLE_SIZE_BYTE/VALUE_SIZE_BYTE)
#define ALLOCABLE_SIZE_BLOCK (ALLOCABLE_SIZE_BYTE/BLOCK_SIZE_BYTE)

#define FREE_TABLE_TO_RAM(i) (RAM_SIZE_BYTE-VALUE_SIZE_BYTE-(i)*VALUE_SIZE_BYTE)
#define RAM_TO_FREE_TABLE(i) (CEIL_DIV(RAM_SIZE_BYTE-VALUE_SIZE_BYTE-(i),VALUE_SIZE_BYTE))
#define FREE_TABLE_TO_REF(i) (RAM_SIZE_BYTE-BLOCK_SIZE_BYTE-(i)*BLOCK_SIZE_BYTE)
#define REF_TO_FREE_TABLE(i) (CEIL_DIV(RAM_SIZE_BYTE-BLOCK_SIZE_BYTE-(i),BLOCK_SIZE_BYTE))

/*
RAM_SIZE_BYTE=TAB_SIZE_BYTE+ALLOCABLE_SIZE_BYTE
RAM_SIZE_BYTE=ALLOCABLE_SIZE_BYTE/BLOCK_SIZE_BYTE*VALUE_SIZE_BYTE+ALLOCABLE_SIZE_BYTE
RAM_SIZE_BYTE=ALLOCABLE_SIZE_BYTE*(VALUE_SIZE_BYTE/BLOCK_SIZE_BYTE+1)
RAM_SIZE_BYTE=ALLOCABLE_SIZE_BYTE*(VALUE_SIZE_BYTE/BLOCK_SIZE_BYTE+1)
RAM_SIZE_BYTE/(VALUE_SIZE_BYTE/BLOCK_SIZE_BYTE+1)=ALLOCABLE_SIZE_BYTE
RAM_SIZE_BYTE/((VALUE_SIZE_BYTE+BLOCK_SIZE_BYTE)/BLOCK_SIZE_BYTE)=ALLOCABLE_SIZE_BYTE
RAM_SIZE_BYTE*BLOCK_SIZE_BYTE/(VALUE_SIZE_BYTE+BLOCK_SIZE_BYTE)=ALLOCABLE_SIZE_BYTE
*/

#ifdef MALLOCTESTER_MAIN

void write_ram_32(uint8_t *ram, uint32_t addr, uint32_t data)
{
	ram[addr] = data & 0xff;
	ram[addr+1] = (data>>8) & 0xff;
	ram[addr+2] = (data>>16) & 0xff;
	ram[addr+3] = (data>>24) & 0xff;
}

uint32_t read_ram_32(uint8_t *ram, uint32_t addr)
{
	uint32_t data = 0;
	data |= ram[addr+0];
	data |= ram[addr+1] << 8;
	data |= ram[addr+2] << 16;
	data |= ram[addr+3] << 24;
	return data;
}

uint32_t vm_malloc(uint8_t *ram, uint32_t size) // size in bytes
{
	printf("vm_malloc:\n");
	printf("\tsize: %u bytes = ", size);
	uint64_t i, j;
	size = CEIL_DIV(size, BLOCK_SIZE_BYTE);
	printf("%u blocks\n", size);
	for(i = 0 ; i < TAB_SIZE_VALUE-size ; i++) {
		printf("\ttrying block %lu (ram %lu)\n", i, FREE_TABLE_TO_RAM(i));
		for(j = 0 ; j < size ; j++) {
			if(read_ram_32(ram, FREE_TABLE_TO_RAM(i+j))!=0) {
				printf("\tfailed on block %lu (ram %lu)\n", i+j, FREE_TABLE_TO_RAM(i+j));
				i += read_ram_32(ram, FREE_TABLE_TO_RAM(i+j))-1;
				break;
			}
		}
		if(j == size) {
			printf("\tblock ok\n");
			write_ram_32(ram, FREE_TABLE_TO_RAM(i), size);
			return FREE_TABLE_TO_REF(i);
		}
	}
	printf("\tno block found, returning null\n");
	return 0;
}

void vm_free(uint8_t *ram, uint32_t addr)
{
	printf("vm_free:\n");
	printf("\taddr = %u (block %lu, ram %lu)\n", addr, REF_TO_FREE_TABLE(addr), FREE_TABLE_TO_RAM(REF_TO_FREE_TABLE(addr)));
	write_ram_32(ram, FREE_TABLE_TO_RAM(REF_TO_FREE_TABLE(addr)), 0);
}

void vm_free_table_setup(uint8_t *ram)
{
	uint64_t i;
	printf("vm_free_table_setup:\n");
	printf("\ttable: %ld bytes = %ld values = %ld blocks\n", TAB_SIZE_BYTE, TAB_SIZE_VALUE, TAB_SIZE_BLOCK);
	for(i = 0 ; i < TAB_SIZE_BYTE ; i++) {
		write_ram_32(ram, FREE_TABLE_TO_RAM(i), 0);
	}
	write_ram_32(ram, FREE_TABLE_TO_RAM(0), TAB_SIZE_BLOCK);
}

void dump_ram_8(uint8_t *ram)
{
	uint64_t i;
	printf("ram (8b): ");
	for(i = RAM_SIZE_BYTE-64 ; i < RAM_SIZE_BYTE ; i++) {
		printf("[%lu]=0x%02x ", i, ram[i]);
	}
	printf("\n");
}

void dump_ram_32(uint8_t *ram)
{
	uint64_t i;
	printf("ram (32b): ");
	for(i = RAM_SIZE_BYTE-64 ; i < RAM_SIZE_BYTE ; i += 4) {
		printf("[%lu]=0x%08x ", i, read_ram_32(ram, i));
	}
	printf("\n");
}

int main()
{
	uint64_t i;
	uint64_t z, a, b, c, d;
	uint8_t *ram;
	ram = malloc(RAM_SIZE_BYTE);
	if(ram == NULL)
		return 1;
	memset(ram, 0, RAM_SIZE_BYTE);
	printf("VALUE_SIZE_BYTE=%ld\n", VALUE_SIZE_BYTE);
	printf("BLOCK_SIZE_BYTE=%ld\n", BLOCK_SIZE_BYTE);
	printf("RAM_SIZE_BYTE=%ld\n", RAM_SIZE_BYTE);
	printf("TAB_SIZE_BYTE=%ld\n", TAB_SIZE_BYTE);
	printf("ALLOCABLE_SIZE_BYTE=%ld\n", ALLOCABLE_SIZE_BYTE);
	printf("TAB_SIZE_VALUE=%ld\n", TAB_SIZE_VALUE);
	printf("TAB_SIZE_BLOCK=%ld\n", TAB_SIZE_BLOCK);
	printf("ALLOCABLE_SIZE_VALUE=%ld\n", ALLOCABLE_SIZE_VALUE);
	printf("ALLOCABLE_SIZE_BLOCK=%ld\n", ALLOCABLE_SIZE_BLOCK);
	printf("ALLOCABLE_SIZE_BYTE+TAB_SIZE_BYTE=%ld\n", ALLOCABLE_SIZE_BYTE+TAB_SIZE_BYTE);
	printf("ALLOCABLE_SIZE_BYTE+TAB_SIZE_BYTE-RAM_SIZE_BYTE=%ld\n", ALLOCABLE_SIZE_BYTE+TAB_SIZE_BYTE-RAM_SIZE_BYTE);
	printf("\n");
	/**/
	for(i = 0 ; i < RAM_SIZE_BYTE ; i++) {
		if(i == 70)
			i = RAM_SIZE_BYTE-70;
		printf("REF_TO_FREE_TABLE(%lu)=%ld\n", i, REF_TO_FREE_TABLE(i));
	}
	printf("\n");
	for(i = 0 ; i < TAB_SIZE_VALUE ; i++) {
		if(i == 70)
			i = TAB_SIZE_VALUE-70;
		printf("FREE_TABLE_TO_REF(%lu)=%ld\n", i, FREE_TABLE_TO_REF(i));
	}
	printf("\n");
	for(i = TAB_SIZE_VALUE ; i < RAM_SIZE_BYTE ; i++) {
		if(i == TAB_SIZE_VALUE+70)
			i = RAM_SIZE_BYTE-70;
		printf("RAM_TO_FREE_TABLE(%lu)=%ld\n", i, RAM_TO_FREE_TABLE(i));
	}
	printf("\n");
	for(i = 0 ; i < TAB_SIZE_VALUE ; i++) {
		if(i == 70)
			i = TAB_SIZE_VALUE-70;
		printf("FREE_TABLE_TO_RAM(%lu)=%ld\n", i, FREE_TABLE_TO_RAM(i));
	}
	/**/
	dump_ram_32(ram);
	vm_free_table_setup(ram);
	dump_ram_32(ram);
	z = vm_malloc(ram, 15);
	printf("z=%lu\n", z);
	dump_ram_32(ram);
	a = vm_malloc(ram, 10);
	printf("a=%lu\n", a);
	dump_ram_32(ram);
	b = vm_malloc(ram, 20);
	printf("b=%lu\n", b);
	dump_ram_32(ram);
	vm_free(ram, a);
	dump_ram_32(ram);
	c = vm_malloc(ram, 12);
	printf("c=%lu\n", c);
	dump_ram_32(ram);
	d = vm_malloc(ram, 32);
	printf("d=%lu\n", d);
	dump_ram_32(ram);
	return 0;
}

#endif