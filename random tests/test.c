/*	These tests are meant to:
	[X] Show a test program that correctly uses allocation in a non­trivial way behaves 
		correctly.
	[/] Show that after allocating and deallocating memory, trying to deallocate an invalid 
		address is immediately detected.
	[X] Show that after allocating and deallocating memory, trying to deallocate an already 
		freed region is immediately detected.
	[/] Show that after allocating and deallocating memory, trying to deallocate a valid region 
		by passing in a pointer inside the region is immediately detected.
	[X] Show that allocating memory and then exiting triggers the leak detector and shows 
		where the leak occurred.

	Experiment with other memory allocation mistakes to see what you are able to detect.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "slug_mem.h"

/* Comment this out to make the program exit cleanly with no allocations */
/* #define NOALLOC */

int main(int argc, char *argv[]) {
	void* allocs[100], big_alloc[1000];
	int i, num = 0;

	#ifndef NOALLOC

	/* Valid sized allocations */
	allocs[num++] = malloc(sizeof(char)); 
	allocs[num++] = malloc(sizeof(short));
	allocs[num++] = malloc(sizeof(int));
	allocs[num++] = malloc(sizeof(long));
	allocs[num++] = malloc(sizeof(unsigned long));
	allocs[num++] = malloc(sizeof(float)); 
	allocs[num++] = malloc(sizeof(double));

	allocs[num++] = malloc(134217727);	/* Valid */
	allocs[num++] = malloc(134217728);	/* Valid */
	allocs[num++] = malloc(0);	/* Invalid, 0 MB, print error to stderr and skip malloc */
	/* allocs[num++] = malloc(134217729); */	/* Invalid, >128 MB, print error to stderr and exit */

	/* Make sure programmer did not allocate too many entries */
	assert(num < 100);

	printf("All allocations made.\n");

	/* Free all valid allocations in the array */
	for(i = 0; i < 9; i++){
		free(allocs[i]);
	}

	/* Allocate and free many regions in a tight loop*/
	for(i = 0; i < 1000; i++){
		big_alloc[i] = malloc(sizeof(char));
		free(big_alloc[i]);
	}

	/* free(allocs[0]); */	/* Invalid, freeing invalid/freed memory, print error to stderr and exit */
 
	printf("All frees made.\n");
	#endif

	/* Exiting should print a table of unfreed memory and statistics
	 * unless NOALLOC is not defined
	 */
	return 0;
}