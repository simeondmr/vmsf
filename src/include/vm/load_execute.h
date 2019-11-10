#ifndef __LOAD_EXECUTE
#define __LOAD_EXECUTE
#include <stdint.h>
#include "../hardware/io.h"

uint32_t load_execute(char *filename, struct ports *prts);

#endif