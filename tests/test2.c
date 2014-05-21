/*	This test is meant to:
	Show a test program that correctly uses allocation in a non­trivial way behaves 
	correctly. It will also show that correct use of allocations will cause statistics to
	display on exit, but no memory table will print.
	Expected output is "1" and statistics.
*/

#include <stdio.h>
#include <stdlib.h>

#include "slug_mem.h"

int main(int argc, char *argv[]) {
	int *ptr;

	ptr = (int*)malloc(sizeof(int));

	*ptr = 1;
	printf("%d\n", *ptr);

	free(ptr);

	return 0;
}
