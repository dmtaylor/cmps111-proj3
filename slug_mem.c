/* slug_mem.c : An implementation file for the slug memory package
 * 
 * A wrapper for malloc and free which does memory diagnostics
 *
 * By: Forrest Kerslager, Nick Noto, David Taylor, Kevin Yeap, Connie
 *       Yu
 */

#include <stdlib.h>
#include <stdio.h>

#include "hashset.h"

void* slug_malloc(size_t size, char* WHERE){
    /* TODO */
}

void slug_free(void* addr, char* WHERE){
    /* TODO */
}

void slug_memstats(void){
    /* TODO */
}
