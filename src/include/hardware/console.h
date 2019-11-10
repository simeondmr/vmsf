#ifndef __CONSOLE_H
#define __CONSOLE_H
#include "io.h"
#define CONSOLE_HW 0x00
#define PRINT_CHAR_PTR 0x00

void *console(void *ptr);
pthread_t *init_console(struct ports *prts);
void print_char(struct ports *prts);

#endif