/* meminfo_hash.c : Implementation file for int hashing
 * By: David Taylor, et. all
 */

#include<stdint.h>

uint32_t meminfo_hash(void* item)
{
    uint32_t itemval = (uint32_t) item;
    uint32_t returnval = (uint32_t)item * ((uint32_t)item + 1 ) % 81181;

    return returnval;
}

