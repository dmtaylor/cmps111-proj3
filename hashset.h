/* hashset.h : Header file for the hashset used to keep track
 *              of memory.
 * 
 * By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, 
 *     Connie Yu.
 */

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <stdbool.h>

#include "meminfo.h"

struct hashset {
	size_t length;
	int load;
	meminfo_ref* array;
};

typedef struct hashset *hashset_ref;

/*
 * Create a new hashset with a default number of elements.
 */
hashset_ref new_hashset (void);

/*
 * Frees the hashset, and the structs it points at.
 */
void free_hashset (hashset_ref);

/*
 * Inserts a new meminfo_ref into the hashset.
 */
void put_hashset (hashset_ref, meminfo_ref);

/*
 * Removes a given meminfo_ref from the hashset by invalidating the data
 */
void remove_hashset(hashset_ref, void*);

/*
 * Looks up the memory address in the hashset and returns pointer if found,
 * NULL if not found.
 */
meminfo_ref has_hashset (hashset_ref, void*);

/*
 * Prints out the entries in the hash table.
 */
void print_hash(hashset_ref hashset);

#endif
