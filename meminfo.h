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
    return temp;

}

/* Not sure if necessary */

/*void free_meminfo(meminfo_ref elim){
    free(elim);
    return;
}*/


#endif
