#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid = -1;
	pid = fork();
	if(pid == 0)
	{
		while(1)
		{
			printf("子进程\n");
			sleep(5);
		}
	}
	else if(pid > 0)
	{
	//	abort();
		exit(0);	
	}
	return 0;
}
