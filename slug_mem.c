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
#include "slug_mem.h"

#define BASE_ARRAY_SIZE 32

hashset_ref mem_set = NULL;
uint32_t* size_array;
uint32_t curr_size_size;
uint32_t curr_size_loc; /* Points to the next space to be filled */


void* slug_malloc(size_t size, char* WHERE)
{
	meminfo_ref entry;
	void* mem_addr;
	struct timeval tv;
	int err;
	double ticks;
	int iter;
	uint32_t* temp_size_array;
	
	if(mem_set == NULL){
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
	put_hashset(mem_set, entry);
	
	/* insert size into size array, this array will be global and require array doubling */
	if(curr_size_loc == curr_size_size -1){
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
    if(mem_set == NULL){
		fprintf(stderr, "slug_mem: error: No memory allocated, don't do that!");
		return;
	}
    
    /* TODO */
}

void slug_memstats(void)
{
	uint32_t total_allocations;
	uint32_t current_allocations;
	uint32_t amount_currently_allocated;
	uint32_t mean_allocated;
	double standard_deviation_allocated;
	
	if(mem_set == NULL){
		fprintf(stdout, "No dynamic memory allocation has been done. \
		Congrats!\n");
		return;
	}
	
    /*traverse hashtable kept by slug_malloc & print the following for each allocation:
      size, timestamp, address, file, line number */
    for (size_t index = 0; index < mem_set->length; index++){
        if(hashset->array[index] != NULL){
            if (!mem_stat->array[index]->tombstone){
                printf("Info Regarding Current Allocations:\n");
                printf("Index: %d\tSize of: %d\tTime Allocated: %d\tAddress of: %d\tLocated in File: %s\t\n", 
                        index, mem_stat->array[index]->size, mem_stat->array[index]->time, mem_stat->array[index]->address, mem_stat->array[index]->location);
            }
        }
    }
    
    /*Print # of total allocations*/
    printf("Total Number of Allocations: %d", total_allocations);
    
    /*Print # of current allocations*/
    printf("Number of Current Allocations: %d", current_allocations);
    
    /*Print amount of memory currently allocated*/
    printf("Amount of Memory Currently Allocated: %d", amount_currently_allocated);
    
    /*Print mean of memory currently allocated*/
    printf("Mean Size of Memory Currently Allocated: %d", mean_allocated);
    
    /*Print standard deviation of memory currently allocated*/
    printf("Standard Deviation of Current Allocations: %d", standard_deviation_allocated);
}
