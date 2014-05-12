/* slug_mem.c : An implementation file for the slug memory package
 * 
 * A wrapper for malloc and free which does memory diagnostics
 *
 * By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, Connie
 *       Yu
 */

#include <stdlib.h>
#include <stdio.h>

/* Filler entry for include of hastable.
   Might require a global variable, might not.
   For now assume no reference is needed and functions are called
   directly.
   DOES NOT WORK
*/
#include "hashset.h"

void* slug_malloc(size_t size, char* WHERE)
{
	meminfo_ref entry;
	void* mem_addr;
	struct timeval tv;
	int err;
	double ticks;

	/* Check for the minimum and maximum block size */
	if (size == 0) {
		fprintf(stderr,"slug_malloc: error: Cannot allocate a zero size block.\n");
	}

	/* sizeof returns bytes, check for a size >= 128 MB in bytes */
	if (size > 134217728) {
		fprintf(stderr,"slug_malloc: error: Cannot allocate block size greater than 128MB.\n");
		exit(EXIT_FAILURE);
	}

	/* Allocate the memory and store its location */
	mem_addr = malloc(size);
	if (mem_addr == NULL) {
		/* error */
	}

	/* Get the time of allocation */
	err = gettimeofday(&tv, NULL);
	if(!err) {
		ticks = tv.tv_sec + tv.tv_usec * 1e-6;
	} else {
		fprintf(stderr,"slug_malloc: error: Time resolution failed.\n");
		exit(EXIT_FAILURE);
	}

	/* Create entry for hash table */
	entry = new_meminfo(size, ticks, mem_addr, WHERE)

	/* insert entry into hash, hashed by mem_addr */
	/* insert size into size array, this array will be global and require array doubling */
}

void slug_free(void* addr, char* WHERE)
{
    /* TODO */
}

void slug_memstats(void)
{
    /* TODO */
}
