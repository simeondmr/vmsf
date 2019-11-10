#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/hardware/io.h"
#include "../include/hardware/int_table.h"
#include "../include/hardware/console.h"
#include "../include/vm/registers_flags.h"

void *console(void *ptr)
{
	struct ports *prts = (struct ports *) ptr;
	while(1) {
		pthread_mutex_lock(&prts->mutex);
		pthread_cond_wait(&prts->p_cond, &prts->mutex);
		pthread_mutex_unlock(&prts->mutex);
		if (prts->p1 == CONSOLE_HW) {
			int_table[prts->p2](prts);
		}
	}
	return 0;
}

pthread_t *init_console(struct ports *prts) 
{
	pthread_t *cnsl = malloc(sizeof(pthread_t));
	pthread_create(cnsl, NULL, &console, prts);
	return cnsl;
}

void print_char(struct ports *prts) 
{
	pthread_mutex_lock(&prts->mutex);
	pthread_cond_wait(&prts->ready_cond, &prts->mutex);
	printf("%c", (char) prts->p3);
	fflush(stdout);
	pthread_mutex_unlock(&prts->mutex);
}

