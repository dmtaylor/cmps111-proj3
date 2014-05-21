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
uint32_t* size_array;	/* Stores the size of each allocation */
uint32_t curr_size_size;
uint32_t curr_size_loc;	/* Points to the next space to be filled */
int flag_exithdl = 0; 	/* Set to 1 when exit handler is installed */

/* Prototypes */
void* slug_malloc(size_t, char*);
void slug_free(void*, char*);
void slug_memstats(void);


/* Prints the statistics of all memory allocations.
 * This exit handler is installed during the first call to slug_malloc() 
 */
void handleExit(void) {
	slug_memstats();
	free_hashset(mem_set);
}


/* slug_malloc() checks for common malloc errors and records statistical information.
 * size is the size the of the desired memory allocations. 
 * WHERE is a string inserted by directives in slug_mem.h that contains 
 *    the file and line number of the original call to malloc().
 * Return Value: Returns a pointer to the allocated memory.
 */
void* slug_malloc(size_t size, char* WHERE)
{
	int err, iter;
	double ticks;
	uint32_t* temp_size_array;
	meminfo_ref entry;
	void* mem_addr = NULL;
	struct timeval tv;
	
	if(mem_set == NULL) {
		mem_set = new_hashset();
		size_array = calloc(BASE_ARRAY_SIZE, sizeof(uint32_t));
		curr_size_size = BASE_ARRAY_SIZE;
		curr_size_loc = 0;
	}

	/* Check for the minimum and maximum block size, skip malloc if zero */
	if (size == 0) {
		fprintf(stderr,"slug_malloc:%s: warning: Cannot allocate a zero size block.\n", WHERE);
	}

	/* sizeof returns bytes, check for a size >= 128 MB in bytes */
	if (size > 134217728) {
		fprintf(stderr,"slug_malloc:%s: error: Cannot allocate block size greater than 128MB.\n", WHERE);
		exit(EXIT_FAILURE);
	}

	/* Get the time of allocation */
	err = gettimeofday(&tv, NULL);
	if(!err) {
		ticks = tv.tv_sec + tv.tv_usec * 1e-6;
	} else {
		fprintf(stderr,"slug_malloc:%s: error: Time resolution failed.\n", WHERE);
		exit(EXIT_FAILURE);
	}

	/* Allocate the memory and store its location */
	if (size != 0) {
		mem_addr = malloc(size);
		if (mem_addr == NULL) {
			fprintf(stderr, "slug_malloc:%s: error: Call to malloc failed.\n", WHERE);
			exit(EXIT_FAILURE);
		}

		/* Create entry for hash table */
		entry = new_meminfo(size, ticks, mem_addr, WHERE);

		/* Insert entry into hash, hashed by mem_addr */
		put_hashset(mem_set, entry);
	}

	/* Install exit handler */
	if (!flag_exithdl) {
		flag_exithdl = 1;
		if (atexit(handleExit)) {
			fprintf(stderr, "slug_malloc:%s: error: Cannot set exit handler.\n", WHERE);
			exit(EXIT_FAILURE);
		}
	}

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

	return mem_addr;
}


/* slug_free() checks for common freeing errors.
 * addr is a pointer to the allocation to free. 
 * WHERE is a string inserted by directives in slug_mem.h that contains 
 *    the file and line number of the original call to free().
 */
void slug_free(void* addr, char* WHERE)
{
    if(mem_set == NULL) {
		fprintf(stderr, "slug_mem:%s: error: No memory allocated, don't do that!", WHERE);
		return;
	}
    
    if(has_hashset(mem_set, addr) == NULL) {
        fprintf(stderr, "slug_mem:%s: error: Tried to free unallocated memory.\n", WHERE);
        exit(EXIT_FAILURE);
    }

    remove_hashset(mem_set, addr);
    free(addr);
}


/* slug_memstats() reports statistics on historical and current allocations. */
void slug_memstats(void)
{
	uint32_t amount_currently_allocated = 0;
	double mean_allocated = 0.0;
    double variance = 0.0;
	double standard_deviation_allocated = 0.0;
    size_t index;
    
	/* Print current memory allocations */
	if(mem_set == NULL) {
		fprintf(stdout, "No dynamic memory allocation has been done. Congrats!\n");
		return;
	} else {
		printf("Unfreed Memory\n=============================\n");
		print_hash(mem_set);
		printf("\n");
    }

	/* Print statistics of all memory allocation */
	printf("Statistics\n=============================\n");
    printf("Total Number of Allocations: %d\n", curr_size_loc);
    printf("Number of Current Allocations: %d\n", mem_set->load);
    
    /* Print amount of memory currently allocated */
    for (index = 0; index < mem_set->length; index++) {
		if(mem_set->array[index] != NULL  && !mem_set->array[index]->tombstone) {
			amount_currently_allocated += mem_set->array[index]->size;
		}
    }
    printf("Amount of Memory Currently Allocated: %u\n", amount_currently_allocated);
    
    /* Print mean of allocated */
    for (index = 0; index < curr_size_loc ; index++) {
        mean_allocated += size_array[index];
    }
    mean_allocated /= curr_size_loc;
    printf("Mean Size of Memory Allocated: %lf\n", mean_allocated);
    
    /* Print standard deviation of memory allocated */
    for(index = 0; index < curr_size_loc; index++) {
        variance += pow(((double)size_array[index] - mean_allocated), 2);
    }
    variance /= curr_size_loc - 1;
    standard_deviation_allocated = sqrt(variance);
    printf("Standard Deviation of Allocations: %lf\n", standard_deviation_allocated);
}
