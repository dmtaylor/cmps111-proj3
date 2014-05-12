#ifndef __MEMINFO_H__
#define __MEMINFO_H__

#include <stdlib.h>

typedef struct meminfo *meminfo_ref;
typedef struct meminfo {
    size_t size;
    time_t time;
    void* address;
    char* location;
} meminfo_t;


#endif