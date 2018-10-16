#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

void my_func(int a)
{
	printf("hhh\n");
}

void my_func2(int a)
{
	printf("hhh\n");
}
int main(int argc,char * argv[])
{
	struct itimerval new_value;
	new_value.it_interval.tv_sec = 1;
	new_value.it_interval.tv_usec = 0;

	new_value.it_value.tv_sec = 1;
	new_value.it_value.tv_usec = 0;
	
	signal(SIGALRM,my_func);
	alarm(2);
	//setitimer(ITIMER_REAL,&new_value,NULL);
	while(1)
	{

	}
	return 0;
}
