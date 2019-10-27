#include <stdio.h>
#include "../include/vm.h"
#include "../include/load_execute.h"

int main(int argc, char *argv[])
{
	if (!load_execute(argv[1]))
		fprintf(stderr, "Error: problem during loading rom\n");
	else
		fprintf(stdout, "Execution completed\n");
	return 0;
}