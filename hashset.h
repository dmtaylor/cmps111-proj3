// $Id: hashset.h,v 1.1 2012-11-16 18:05:22-08 - - $

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <stdbool.h>

#include "meminfo.h"

typedef struct hashset *hashset_ref;

/*
// Create a new hashset with a default number of elements.
*/
hashset_ref new_hashset (void);

/*
// Frees the hashset, and the words it points at.
*/
void free_hashset (hashset_ref);

/*
// Inserts a new meminfo_ref into the hashset.
*/
void put_hashset (hashset_ref, meminfo_ref);

/*
 * Removes a given meminfo_ref from the hashset by invalidating the data
 */
void remove_hashset(hashset_ref, meminfo_ref);

/*
// Looks up the meminfo_ref in the hashset and returns pointer if found,
// NULL if not found.
*/
meminfo_ref has_hashset (hashset_ref, meminfo_ref);

void print_debug(hashset_ref hashset);
void print_hash(hashset_ref hashset);
#endif

