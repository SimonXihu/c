#include <stdio.h>
#include <sys/time.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void myfunc(int sig)
{
	printf("recv sig = %d\n",sig);
	time_t thistime = 0;
	thistime = time(NULL);
	struct tm *thistm;
	thistm = localtime(&thistime);
	char *cur = asctime(thistm);
	char buf[BUFSIZ];
	bzero(buf,BUFSIZ);
	sprintf(buf,"时间是：%s\n",cur);
	int fd = open("./time.txt",O_WRONLY|O_APPEND|O_CREAT,0777);
	if(fd < 0)
	{
		perror("setsid");
	}		
	write(fd,buf,sizeof(buf));
	close(fd);
}
int main(void)
{
	pid_t pid = -1;
	pid_t sid = -1;
	pid = fork();
	if(pid == 0)
	{
		//子进程
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		sid = setsid();
		if(sid == -1)
		{
			perror("setsid");
		}
		printf("sid = %d,pid = %d\n",sid,getpid());
		struct sigaction act;
		bzero(&act,sizeof(act));
		act.sa_handler = myfunc;
		act.sa_flags = 0;
		sigaction(SIGALRM,&act,NULL);
		struct itimerval new_value;
		bzero(&new_value,sizeof(new_value));
		new_value.it_interval.tv_sec = 2;
		new_value.it_interval.tv_usec = 0;
		new_value.it_value.tv_sec = 5;
		new_value.it_value.tv_usec = 0;

		int ret = setitimer(ITIMER_REAL,&new_value,NULL);
		if(ret != 0)
		{
			perror("setitimer");
		}
		while(1);
	}
	else if(pid > 0)
	{
		printf("father old sid = %d,pid = %d\n",getsid(0),getpid());
		exit(0);
	}
	else
	{
		perror("fork");
	}
	return 0;
}
