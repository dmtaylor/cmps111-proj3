/* meminfo_hash.c : Implementation file for int hashing
 * By: David Taylor, et. all
 */
/* Check this hash function */

uint32_t meminfo_hash(void* item){
    uint32_t itemval = (uint32_t) item;
    uint32_t returnval = item * (item +1) % 81181;
    return returnval;
}

