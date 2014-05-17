#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "meminfo.h"

meminfo_ref new_meminfo(size_t new_size, time_t new_time, void* new_addr,
                        char* new_location)
{
    meminfo_ref temp = malloc(sizeof(meminfo_t));
    assert(temp != NULL);

    temp->size = new_size;
    temp->time = new_time;
    temp->address = new_addr;
    temp->location = new_location;
    temp->tombstone = 0;

    return temp;
}