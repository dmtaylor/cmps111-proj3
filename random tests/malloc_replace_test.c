#include<stdio.h>
#include <stdlib.h>
#include "malloc.h"

/*compile with "cc malloc_replace_test"*/

int main(int argc, char *argv[]) {
  
  malloc(sizeof(short)); /*this should be repalced with slug_malloc.*/
  malloc(sizeof(int)); /*this should be repalced with slug_malloc.*/
  malloc(sizeof(double)); /*this should be repalced with slug_malloc.*/
  
  return 0;
}