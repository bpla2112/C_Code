#include<stdio.h>
#include "testmycall.h"

int main(void)
{
	printf("%ld\n", syscall(__NR_bernardo_pla, 3885008));
}
