/* slug_mem.h : A Header file for the slug memory package
 * 
 * A wrapper for malloc, free and memstats which does memory diagnostics.
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
 
#define FUNCTIONIZE(a,b) a(b) /*generic function caller*/
#define STRINGIZE(a) #a /*function that turns a number into a string*/
#define INT2STRING(i) FUNCTIONIZE(STRINGIZE,i) /*calls the generic function.*/
#define WHERE __FILE__ ":" INT2STRING(__LINE__) /*WHERE is a pointer an array of characters*/
#define malloc(s) slug_malloc((s), WHERE) /*replace all malloc with slug_malloc*/
#define free(t) slug_free((t), WHERE) /*replace all free with slug_free*/

void* slug_malloc(size_t, char*);

void slug_free(void*, char*);

void slug_memstats(void);

#endif

