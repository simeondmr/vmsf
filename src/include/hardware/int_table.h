#ifndef __INT_TABLE_H
#define __INT_TABLE_H
#include "console.h"

typedef void (interrupt)(struct ports *prts);

interrupt *int_table[] = {
	print_char
};

#endif