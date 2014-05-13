#include <stdio.h>
#include <stdlib.h>

/*
compile using "cc macro_test.c"
  and run using "./a.out"
*/

/*TEACHER CODE=================================*/
#define FUNCTIONIZE(a,b) a(b) /*generic function caller using a macro*/
#define STRINGIZE(a) #a /*function that turns a number into a string*/
#define INT2STRING(i) FUNCTIONIZE(STRINGIZE,i) /*calls the generic function caller.*/
#define WHERE __FILE__ ":" INT2STRING(__LINE__) /*WHERE is a pointer an array of characters*/
#define malloc(s) slug_malloc((s), WHERE) /*this is to replace all malloc with slug_malloc*/
/*================================================*/
 
  /*my own macros*/
#define number_macro 35       /*number macro*/
#define THIS_IS_REPLACED_WITH_MACRO(x) function(x, WHERE);

int function(int x, char *string);

/*examples*/
main (int argc, char *argv[]) {
  int a;
  printf("number_macro is %d\n", number_macro); /*number_macro is replaced with 35*/
  
  a = THIS_IS_REPLACED_WITH_MACRO(2); /*THIS_IS_REPLACED_WITH_MACRO(2) replaced with function(x, WHERE);*/
  
  printf("this line is in %s\n", WHERE); /*WHERE is replaced by "test.c:30", WHERE[0] == t, */
}

int function(int x, char *string) {
  printf("this line is in %s\n", string);
  x *= 2;
  return x;
}