#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define checkout

void checkout f()
{
	printf("hello\n");
}
int main(void)
{
	time_t t = time(NULL);
	srand((unsigned int)t);
	int rr=0;
	f();
	while(1)
	{
		rr  = rand();
		printf("rr=%d\n",rr);
		sleep(3);
	}
	return 0;
}
