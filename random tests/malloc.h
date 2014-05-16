#include <stdio.h>
#include <stdlib.h>

#define FUNCTIONIZE(a,b) a(b) /*generic function caller*/
#define STRINGIZE(a) #a /*function that turns a number into a string*/
#define INT2STRING(i) FUNCTIONIZE(STRINGIZE,i) /*calls the generic function.*/
#define WHERE __FILE__ ":" INT2STRING(__LINE__) /*WHERE is a pointer an array of characters*/
#define malloc(s) slug_malloc((s), WHERE) /*this is to replace all malloc with slug_malloc*/

int slug_malloc(int size, char *location) {
  printf("\ninteger %d was passed in\nthis line is in %s\n", size, location);
  
  return 0;
}