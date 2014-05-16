/* meminfo.h : Header file for the meminfo struct used to keep track
 * of memory.
 * By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap,
 * 		Connie Yu
 * 16.05.2014
 * 
 */

#ifndef __MEMINFO_H__
#define __MEMINFO_H__

#include <stdlib.h>
#include <assert.h>

typedef struct meminfo *meminfo_ref;
typedef struct meminfo {
    size_t size;
    time_t time;
    void* address;
    char* location;
    char tombstone;
} meminfo_t;


/* NOTE: Get parameters prior to calling */
meminfo_ref new_meminfo(size_t new_size, time_t new_time, void* new_addr,
                        char* new_location){

    meminfo_ref temp = malloc(sizeof(meminfo_t));
    assert(temp != NULL);
    temp->size = new_size;
    temp->time = new_time;
    temp->address = new_addr;
    temp->location = new_location;
    temp->tombstone = 0;
    return temp;

}

/* Not sure if necessary */

/*void free_meminfo(meminfo_ref elim){
    free(elim);
    return;
}*/


#endif
