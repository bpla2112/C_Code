#include <stdlib.h>
#include <stdio.h>
#include "testcall.h"

int main(void)
{
	void * garbage;
	
	for(int i=0; i<9; i++) {
		garbage = malloc(sizeof(size_t)*8);
	}
	printf("Claimed: %li\n", syscall(__NR_sys_get_slob_amt_claimed));
	printf("Freed %li\n", syscall(__NR_sys_get_slob_amt_free));
	
	return 0;
}
