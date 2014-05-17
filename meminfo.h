/* meminfo.h : Header file for the meminfo struct used to keep track
 * of memory.
 *
 * By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap,
 * 		Connie Yu
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

meminfo_ref new_meminfo(size_t, time_t, void*, char*);

#endif
