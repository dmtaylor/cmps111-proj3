/* hashset.c : Implementation file for the hashset used to keep track
 *              of memory.
 * 
 * By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, 
 *     Connie Yu.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashset.h"
#include "meminfo_hash.h"
#include "meminfo.h"

#define HASH_NEW_SIZE 15


hashset_ref new_hashset (void) 
{
	size_t index;

	hashset_ref new = malloc (sizeof (struct hashset));
	assert (new != NULL);

	new->length = HASH_NEW_SIZE;
	new->load = 0;
	new->array = malloc (new->length * sizeof (meminfo_ref));
	assert (new->array != NULL);

	for (index = 0; index < new->length; ++index) {
		new->array[index] = NULL;
	}

	return new;
}

void free_hashset (hashset_ref hashset) 
{
	size_t i;

	for (i = 0; i < hashset->length; i++){
		free(hashset->array[i]);
		hashset->array[i] = NULL;
	}

	memset (hashset->array, 0, hashset->length * sizeof (meminfo_ref));
	free (hashset->array);
	memset (hashset, 0, sizeof (struct hashset));
	free (hashset);
}

bool too_full_hash(hashset_ref hashset)
{
   return hashset->load * 4 > (int)hashset->length;
}


void double_array_hash(hashset_ref hashset)
{
	size_t i;
	bool exists;
	uint32_t index;
	size_t new_length = 2 * hashset->length + 1;

	meminfo_ref* new_array = malloc(new_length * sizeof (meminfo_ref));
	for (index = 0; index < new_length; ++index) {
		new_array[index] = NULL;
	}   

	for (i = 0; i<hashset->length; i++) {
		bool exists = false;
		if (hashset->array[i] != NULL) {
			/* Deletes unused meminfos when resizing array */
			if(hashset->array[i]->tombstone) {
				free(hashset->array[i]);
				continue;
			}

			index = meminfo_hash(hashset->array[i]->address) % new_length;

			while (new_array[index] != NULL) {
				if (new_array[index]->address == hashset->array[i]->address  && !hashset->array[index]->tombstone) {
					exists = true;
					break;
				}
				index = (index + 1) % new_length;
			}
			if(!exists) {
				new_array[index] = hashset->array[i];
			}
		}
	}

	free(hashset->array);
	hashset->length = new_length;
	hashset->array = new_array;
}


meminfo_ref has_hashset (hashset_ref hashset, void* address) 
{
	uint32_t code = meminfo_hash (address) % hashset->length;
	while (hashset->array[code] != NULL) {
		if ((hashset->array[code]->address == address) && (!hashset->array[code]->tombstone)) {
			return hashset->array[code];
		}
		code = (code + 1) % hashset->length;
	}

	return NULL;
}


void put_hashset (hashset_ref hashset, meminfo_ref item) 
{
	uint32_t index;

	if (too_full_hash (hashset)) {
		double_array_hash (hashset);
	}

	if(has_hashset(hashset, item->address) != NULL) {
		free(item);
		return;
	}

	index = meminfo_hash (item->address) % hashset->length;
	while (hashset->array[index] != NULL) {
		if(hashset->array[index]->tombstone) {
			free(hashset->array[index]);
			break;
		}
		index = (index + 1) % hashset->length;
	}

	hashset->array[index] = item;
	hashset->load++;
}


void remove_hashset (hashset_ref hashset, void* address)
{
	uint32_t index;

	if(has_hashset(hashset, address) == NULL) {
		fprintf(stderr, "Cannot remove from memory\n");
		return;
	}

	index = meminfo_hash (address) % hashset->length;

	while (hashset->array[index] != NULL) {
		if (hashset->array[index]->address == address) {
			hashset->array[index]->tombstone = 1;
			hashset->load--;
			return;
		}
		index = (index + 1) % hashset->length;
	}
}


void print_hash(hashset_ref hashset)
{
	size_t index;

	for (index = 0; index < hashset->length; index++) {
		if(hashset->array[index] != NULL  && !hashset->array[index]->tombstone) {
			printf("Address: %p Size: %u Time: %lf Location: %s\n",
				hashset->array[index]->address, 
				hashset->array[index]->size, 
				hashset->array[index]->time, 
				hashset->array[index]->location);
		}
	}
}



