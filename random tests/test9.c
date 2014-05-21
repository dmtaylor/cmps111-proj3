/*	
	This program performs a large amount of allocations and frees.
	Its purpose is to observe how much memory is used by the hash table.
*/

#include <stdio.h>
#include <stdlib.h>

#include "slug_mem.h"

int main(int argc, char *argv[]) {
	void *big_alloc[1000];
	int i;

	/* Allocate and free many regions in a tight loop*/
	for(i = 0; i < 1000; i++){
		big_alloc[i] = malloc(sizeof(char));
		free(big_alloc[i]);
	}

	return 0;
}
