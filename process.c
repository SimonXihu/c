#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid = -1;
	int i = 0;
	for(i = 0;i < 5;i++)
	{
		pid = fork();
		if(pid == 0)
		{
			printf("Child Process,i = %d,pid = %d\n",i,getpid());
			sleep(10);
			exit(i);
		}
		else if(pid > 0)
		{
			printf("Father Process\n");
		}
		else
		{
			perror("fork\n");
		}
	}
	int status = 0;
	int pp=-1;
	while((pp = waitpid(-1,&status,WNOHANG)) != -1)
	{
		if(pp == 0)
		{
			continue;
		}
		if(pp > 0)
		{
			if(WIFEXITED(status))
			{
				printf("exit status:%d\n",WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status))
			{
				printf("signal status:%d\n",WTERMSIG(status));
			}
		}
	}
#if 0
	int fd = -1;
	char bufr[BUFSIZ];
	char bufw[BUFSIZ];
	int ret = -1;
	pid_t pid = -1;
	fd = open("./process.txt",O_RDWR|O_CREAT,0777);
	if(fd < 0)
	{
		perror("open");
	}
	bzero(&bufw,sizeof(bufw));	
	bzero(&bufr,sizeof(bufr));	
	ret = write(fd,"hello",sizeof("hello"));
	if(ret < 0)
	{
		perror("write");
	}
	lseek(fd,0,SEEK_SET);
	pid = fork();	
	if(pid == 0)
	{
		//	printf("Child Process\n");
		//	read(fd,bufr,sizeof(bufr));
		//	printf("bufr:%s\n",bufr);	
		execlp("ls","ls","-al",NULL);
	}	
	else if(pid > 0)
	{
		//	printf("Father Process\n");
		//	read(fd,bufw,sizeof(bufw));
		//	printf("bufw:%s\n",bufw);
		execl("./shuzu","shuzu","","NULL");	
	}
	else
	{
		perror("fork\n");
	}
#endif
	return 0;
}
