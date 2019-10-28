#include <stdio.h>
#include "../include/vm.h"
#include "../include/load_execute.h"

int main(int argc, char *argv[])
{
	if (argc == 2) {
		if (!load_execute(argv[1]))
			fprintf(stderr, "Error: problem during loading rom\n");
		else
			fprintf(stdout, "Execution completed\n");
	} else {
		printf("Use: %s <binfile>\n", argv[0]);
	}
	return 0;
}