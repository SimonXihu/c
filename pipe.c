#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


int main(void)
{
	int i = 0;
	pid_t pid = -1;
	int fd[2];
	char bufr[BUFSIZ];
	char bufw[BUFSIZ];

	pipe(fd);
	for(i = 0;i < 2;i++)
	{
		pid = fork();
		if(pid == 0)
		{
			if(i == 0)
			{
				while(1)
				{
					bzero(bufr,sizeof(bufr));
					read(fd[0],bufr,sizeof(bufr));
					printf("bufr:%s\n",bufr);
					sleep(5);
				}
			}
			if(i == 1)
			{
				while(1)
				{
					bzero(bufw,sizeof(bufw));
					strcpy(bufw,"write.....");
					write(fd[1],bufw,sizeof(bufw));
					printf("bufw:%s\n",bufw);
					//sleep(2);
				}
			}
			break;
		}
	}
	close(fd[0]);
	close(fd[1]);
	return 0;
}
