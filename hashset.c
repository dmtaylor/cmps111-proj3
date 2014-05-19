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

	/* 
	DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
				new, new->length, new->array);
	*/

	return new;
}

void free_hashset (hashset_ref hashset) 
{
	size_t i;

	/* DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset); */

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

/* TODO: Check this */
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


/* TODO: Check this */
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


/* TODO: Check this */
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


/* TODO: Check this , should the while loop check for a previous tombstone
         to prevent tombstombing something multiple times
*/
void remove_hashset (hashset_ref hashset, void* address)
{
	uint32_t index;

	/* duplicate check, already in slug_free
	if(has_hashset(hashset, address) == NULL) {
		fprintf(stderr, "Cannot remove from memory\n");
		return;
	}
	*/

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


/* TODO: Modify print statements to print the info */
/*
void print_debug(hashset_ref hashset){
   int size = 0;
   int count_array[hashset->load];
   for (int index = 0; index<hashset->load; index++){
      count_array[index] = 0;
   }
   for (size_t index = 0; index < hashset->length; index++){
      if(hashset->array[index] != NULL) size++;
      else{
         count_array[size]++;
         size = 0;
      }
   }

   printf("%15d words in hash set\n", hashset->load);
   printf("%15d length of the hash array\n", (int)hashset->length);
   for (int index = 1; index<hashset->load; index++){
      if (count_array[index] != 0)
          printf("%15d clusters of size %d\n",count_array[index],index);
   }
}
*/


/* TODO: Check this, format codes are probably wrong */
void print_hash(hashset_ref hashset)
{
	size_t index;

	for (index = 0; index < hashset->length; index++) {
		if(hashset->array[index] != NULL  && !hashset->array[index]->tombstone) {
			printf("Address: %p Size: %u Time: %u Location: %s\n",
				hashset->array[index]->address, 
				hashset->array[index]->size, 
				hashset->array[index]->time, 
				hashset->array[index]->location);
		}
	}
}



