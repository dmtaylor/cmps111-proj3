#include <stdio.h>
#include <stdlib.h>

#include "slug_mem.h"

/*compile with "cc malloc_replace_test"*/

int main(int argc, char *argv[]) {
  
  int* p = malloc(sizeof(short)); /*this should be repalced with slug_malloc.*/
  free(p);
  malloc(sizeof(int)); /*this should be repalced with slug_malloc.*/
  malloc(sizeof(double)); /*this should be repalced with slug_malloc.*/
  
  return 0;
}