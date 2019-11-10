#include <stdlib.h>
#include <stdbool.h>
#include "../include/hardware/io.h"

struct ports *init_port()
{
	struct ports *prts = malloc(sizeof(struct ports));
	prts->ready = false;
	prts->p_cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	prts->ready_cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	prts->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	return prts;
}

uint32_t read_data(struct ports *prts) 
{
	pthread_mutex_lock(&prts->mutex);
	uint32_t data;
	if (prts->ready)
		data = prts->p3;
	else {
		pthread_cond_wait(&prts->ready_cond, &prts->mutex);
		data = prts->p3;
	}
	pthread_mutex_unlock(&prts->mutex);
	return data;
}

void close_ports(struct ports *prts) 
{
	free(prts);
}