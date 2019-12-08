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

void write_p1_p2(uint32_t p1, uint32_t p2, struct ports *prts)
{
	pthread_mutex_lock(&prts->mutex);
	prts->p1 = p1;
	prts->p2 = p2;
	pthread_cond_broadcast(&prts->p_cond);
	pthread_mutex_unlock(&prts->mutex);
}

void write_p3(uint32_t data, struct ports *prts)
{
	pthread_mutex_lock(&prts->mutex);
	while (prts->ready)
		pthread_cond_wait(&prts->ready_cond, &prts->mutex);
	prts->p3 = data;
	prts->ready = true;
	pthread_cond_broadcast(&prts->ready_cond);
	pthread_mutex_unlock(&prts->mutex);
}

uint32_t read_p3(struct ports *prts) 
{
	pthread_mutex_lock(&prts->mutex);
	uint32_t data;
	while (!prts->ready)
		pthread_cond_wait(&prts->ready_cond, &prts->mutex);
	data = prts->p3;
	prts->ready = false;
	pthread_cond_broadcast(&prts->ready_cond);
	pthread_mutex_unlock(&prts->mutex);
	return data;
}

void close_ports(struct ports *prts) 
{
	free(prts);
}