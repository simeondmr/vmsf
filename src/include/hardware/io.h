#ifndef __IO_H
#define __IO_H
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>
#include "../vm/registers_flags.h"

struct ports {
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;
	bool ready;
	pthread_cond_t p_cond;
	pthread_cond_t ready_cond;
	pthread_mutex_t mutex;
};



struct ports *init_port();
void close_ports(struct ports *prts);





#endif