#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "argos_cpu.h"

CPUX86State env;

int test_init()
{
	argos_init(&env);
	
	return 0;
}



int mainh()
{
	int i;
	
	for (i = 0; i < 5; i++) {
		test_init();
		printf("dupa init\n");
		getchar();
	}

	argos_reset(&env);
	printf("dupa reset\n");
	getchar();

	argos_close(&env);
	printf("dupa close\n");
	getchar();

	return 0;	
}

int main()
{
	int i;
	
	for (i = 0; i < 5; i++) {
		int *v = malloc(10);
		printf("dupa init\n");
		getchar();
	}
	return 0;
}
