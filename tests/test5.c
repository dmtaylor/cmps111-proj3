/*	These tests are meant to:
	Show that after allocating and deallocating memory, trying to deallocate a valid region 
	by passing in a pointer inside the region is immediately detected.

	This test will print out each pointer, exit on an error and then print a table and statistics
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "slug_mem.h"

int main(int argc, char *argv[]) {
	double *p, *p2;

	p = malloc(sizeof(double)); 

	p2 = p + 1;

	printf("p = %p	p2 = %p\n",p,p2);

	free(p2);

	printf("Done\n");

	return 0;
}
