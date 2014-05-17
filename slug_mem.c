/* slug_mem.c : An implementation file for the slug memory package
 * 
 * A wrapper for malloc and free which does memory diagnostics.
 *
 * By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, Connie
 *       Yu
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include<sys/time.h>

#include "hashset.h"

#define BASE_ARRAY_SIZE 32

hashset_ref mem_set = NULL;
uint32_t* size_array;
uint32_t curr_size_size;
uint32_t curr_size_loc; /* Points to the next space to be filled */
int flag_exithdl = 0; /* Set to 1 when exit handler is installed. Default: 0 */

void* slug_malloc(size_t, char*);
void slug_free(void*, char*);
void slug_memstats(void);

void handleExit(void) {
	/* fill in the exit procedure, free hash table? */
	slug_memstats();
}

void* slug_malloc(size_t size, char* WHERE)
{
	int err, iter;
	double ticks;
	uint32_t* temp_size_array;
	meminfo_ref entry;
	void* mem_addr;
	struct timeval tv;
	
	if(mem_set == NULL) {
		mem_set = new_hashset();
		size_array = calloc(BASE_ARRAY_SIZE, sizeof(uint32_t));
		curr_size_size = BASE_ARRAY_SIZE;
		curr_size_loc = 0;
	}

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
		fprintf(stderr, "slug_malloc: error: base malloc failed\n");
		exit(EXIT_FAILURE);
	}

	/* Install exit handler */
	if (!flag_exithdl) {
		flag_exithdl = 1;
		if (atexit(handleExit)) {
			fprintf(stderr, "slug_malloc: error: Cannot set exit handler\n");
			exit(EXIT_FAILURE);
		}
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
	entry = new_meminfo(size, ticks, mem_addr, WHERE);

	/* Insert entry into hash, hashed by mem_addr */
	put_hashset(mem_set, entry);
	
	/* Insert size into size array, this array will be global and require array doubling */
	if(curr_size_loc == curr_size_size - 1){
		curr_size_size *= 2;
		temp_size_array = calloc(curr_size_size, sizeof(uint32_t));
		for(iter = 0; iter<=curr_size_loc; iter++){
			temp_size_array[iter] = size_array[iter];
		}
		free(size_array);
		size_array = temp_size_array;
	}
	size_array[curr_size_loc++] = size;
}

void slug_free(void* addr, char* WHERE)
{
    if(mem_set == NULL) {
		fprintf(stderr, "slug_mem: error: No memory allocated, don't do that!");
		return;
	}
    
    /* TODO */
    
    if(has_hashset(mem_set, addr) == NULL) {
        fprintf(stderr, "slug_mem: error: Tried to free unallocated memory.\n");
        exit(EXIT_FAILURE);
    }

	/* When to free mem structs? freeing here means you cannot tombstone in remove_hashset */
    /* free(addr); */
    remove_hashset(mem_set, addr);
}

void slug_memstats(void)
{
	uint32_t amount_currently_allocated;
	uint32_t mean_allocated;
    uint32_t variance = 0;
	double standard_deviation_allocated;
    size_t index;
    
	if(mem_set == NULL) {
		fprintf(stdout, "No dynamic memory allocation has been done. Congrats!\n");
		return;
	}
	
    /* Traverse hashtable kept by slug_malloc & print the following for each allocation:
     * size, timestamp, address, file, line number 
	 */
    /* print_hash(mem_set); */
    
    /* Print # of total allocations */
    printf("Total Number of Allocations: %d\n", curr_size_loc);
    
    /* Print # of current allocations */
    printf("Number of Current Allocations: %d\n", mem_set->load);
    
    /* Print amount of memory currently allocated */
    for (index = 0; index < mem_set->length; index++) {
		if(mem_set->array[index] != NULL  && !mem_set->array[index]->tombstone) {
			amount_currently_allocated += mem_set->array[index]->size;
		}
    }

    printf("Amount of Memory Currently Allocated: %d\n", amount_currently_allocated);
    
    /* Print mean of allocated */
    for (index = 0; index < curr_size_loc ; index++) {
        mean_allocated += size_array[index];
    }
    mean_allocated /= curr_size_loc;

    printf("Mean Size of Memory Allocated: %d\n", mean_allocated);
    
    /* Print standard deviation of memory allocated */
    for(index = 0; index < curr_size_loc; index++) {
        variance += pow(size_array[index] - mean_allocated, 2);
    }
    variance /= curr_size_loc;
    standard_deviation_allocated = sqrt(variance);

    printf("Standard Deviation of Allocations: %d\n", standard_deviation_allocated);
}
