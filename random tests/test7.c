/*	This test is meant to:
	Show that after allocating and deallocating memory, trying to allocate in invalid amount
	of memory will be reported.
	This program will report a warning for allocating a zero size block but continue running.
	It will then print statistics.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "slug_mem.h"

int main(int argc, char *argv[]) {
	void* allocs[100];
	int i = 0, num = 0;

	/* Valid sized allocations */
	allocs[num++] = malloc(sizeof(char)); 
	allocs[num++] = malloc(sizeof(short));
	allocs[num++] = malloc(sizeof(int));
	allocs[num++] = malloc(sizeof(long));
	sleep(1);
	allocs[num++] = malloc(sizeof(unsigned long));
	allocs[num++] = malloc(sizeof(float)); 
	allocs[num++] = malloc(sizeof(double));

	allocs[num++] = malloc(0);

	printf("All allocations made.\n");

	/* Free all valid allocations in the array */
	for(i = 0; i < 7; i++){
		free(allocs[i]);
	}
 
	printf("All frees made.\n");

	return 0;
}
