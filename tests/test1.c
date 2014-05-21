/*	This test is meant to:
	Show a test program that does not use allocation is not affected.
	This program should exit and print "25" without any statistics printed.
*/

#include <stdio.h>
#include <stdlib.h>

#include "slug_mem.h"

int main(int argc, char *argv[]) {
	int i = 0, num = 0;

	for (i = 0; i < 100; i++){
		if ((i % 4) == 0){
			num = num + 4;
		} else {
			num = num - 1;
		}
	}

	printf("%d\n",num);

	return 0;
}
