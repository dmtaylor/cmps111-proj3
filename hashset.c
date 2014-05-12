// Author: Forrest Kerslager, fkerslag@ucsc.edu
// $Id: hashset.c,v 1.49 2012-12-07 19:34:20-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"
#include "meminfo.h"

#define HASH_NEW_SIZE 15

struct hashset {
   size_t length;
   int load;
   meminfo_ref* array;
};

hashset_ref new_hashset (void) {
   hashset_ref new = malloc (sizeof (struct hashset));
   assert (new != NULL);
   new->length = HASH_NEW_SIZE;
   new->load = 0;
   new->array = malloc (new->length * sizeof (meminfo_ref));
   assert (new->array != NULL);
   for (size_t index = 0; index < new->length; ++index) {
      new->array[index] = NULL;
   }
   DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
                new, new->length, new->array);
   return new;
}

void free_hashset (hashset_ref hashset) {
   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   for (size_t i = 0; i < hashset->length; i++){
      free(hashset->array[i]);
      hashset->array[i] = NULL;
   }
   memset (hashset->array, 0, hashset->length * sizeof (meminfo_ref));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

bool too_full_hash(hashset_ref hashset){
   return hashset->load * 4 > (int)hashset->length;
}

void double_array_hash(hashset_ref hashset){
   size_t new_length = 2 * hashset->length + 1;
   meminfo_ref* new_array = malloc(new_length * sizeof (meminfo_ref));
   for (size_t index = 0; index < new_length; ++index) {
      new_array[index] = NULL;
   }   
   
   for (size_t i = 0; i<hashset->length; i++){
      bool exists = false;
      if (hashset->array[i] != NULL){
         uint32_t index = strhash(hashset->array[i]) % new_length;
         while (new_array[index] != NULL) {
            if (strcmp (new_array[index],hashset->array[i]) == 0){
               exists = true;
               break;
            }
            index = (index + 1) % new_length;
         }
         if(!exists) new_array[index] = hashset->array[i];
      }
   }
   
   free(hashset->array);
   hashset->length = new_length;
   hashset->array = new_array;
}

void put_hashset (hashset_ref hashset, meminfo_ref item) {
   if (too_full_hash (hashset)) double_array_hash (hashset);
   uint32_t index = meminfo_hash (item) % hashset->length; 
   while (hashset->array[index] != NULL) {
      if (hashset->array[index] == item) return;
      index = (index + 1) % hashset->length;
   }
   hashset->array[index] = item;
   hashset->load++;
}

bool has_hashset (hashset_ref hashset, meminfo_ref item) {
   uint32_t code = meminfo_hash (item) % hashset->length;
   while (hashset->array[code] != NULL) {
      if (hashset->array[code] == item) return true;
      code = (code + 1) % hashset->length;
   }
   return false;
}

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

void print_hash(hashset_ref hashset){
   for (size_t index = 0; index < hashset->length; index++){
      if(hashset->array[index] != NULL){
         uint32_t code = strhash (hashset->array[index]);
         printf("array[%10d] = %12u \"%s\"\n",
                (int)index, code, hashset->array[index]);
      }
   }
}

