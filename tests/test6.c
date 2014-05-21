/*	These tests are meant to:
	Show that allocating memory and then exiting triggers the leak detector and shows 
	where the leak occurred.
	This test should exit and display a table of 4 allocations that were not freed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "slug_mem.h"

int main(int argc, char *argv[]) {
	void* allocs[100];
	int num = 0;

	allocs[num++] = malloc(sizeof(char)); 
	allocs[num++] = malloc(sizeof(short));
	allocs[num++] = malloc(sizeof(int));
	allocs[num++] = malloc(sizeof(long));
	sleep(1);
	allocs[num++] = malloc(sizeof(unsigned long));
	allocs[num++] = malloc(sizeof(float)); 
	allocs[num++] = malloc(sizeof(double));

	free(allocs[0]);
	free(allocs[1]);
	free(allocs[2]);

	return 0;
}
