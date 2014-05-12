/* slug_mem.h : A Header file for the slug memory package
 * 
 * A wrapper for malloc and free which does memory diagnostics
 *
 * By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, Connie
 *       Yu
 */

#ifndef __SLUG_MEM_H__
#define __SLUG_MEM_H__

#include <stdio.h>
#include <stdlib.h>

#include "hashset.h"
#include "meminfo.h"

void* slug_malloc(size_t size, char* WHERE);

void slug_free(void* addr, char* WHERE);

void slug_memstats(void);

#endif

