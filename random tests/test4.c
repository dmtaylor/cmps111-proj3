/*	This test is meant to:
	Show that after allocating and deallocating memory, trying to deallocate an invalid 
	address is immediately detected.
	This test should exit with an error that an unallocated region was passed to free, and print statistics.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "slug_mem.h"

int main(int argc, char *argv[]) {
	void* allocs[100];
	int i, num = 0;
	void * p = (void *)0x34fec2;

	/* Valid sized allocations */
	allocs[num++] = malloc(sizeof(char)); 
	allocs[num++] = malloc(sizeof(short));
	allocs[num++] = malloc(sizeof(int));
	allocs[num++] = malloc(sizeof(long));
	sleep(1);
	allocs[num++] = malloc(sizeof(unsigned long));
	allocs[num++] = malloc(sizeof(float)); 
	allocs[num++] = malloc(sizeof(double));

	printf("All allocations made.\n");

	/* Free all valid allocations in the array */
	for(i = 0; i < 9; i++){
		free(allocs[i]);
	}
 
	printf("All frees made.\n");

	free(p);

	printf("Done.\n");

	return 0;
}
