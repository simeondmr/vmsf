#include <stdio.h>
#include "../include/vm/vm.h"
#include "../include/vm/load_execute.h"
#include "../include/hardware/console.h"
#include "../include/hardware/io.h"

int main(int argc, char *argv[])
{
	if (argc == 2) {
		struct ports *prts = init_port();
		pthread_t *thread_console = init_console(prts);
		if (!load_execute(argv[1], prts))
			fprintf(stderr, "Error: problem during loading rom\n");
		else
			fprintf(stdout, "Execution completed\n");
		pthread_join(*thread_console, NULL);
	} else {
		printf("Use: %s <binfile>\n", argv[0]);
	}
	return 0;
}