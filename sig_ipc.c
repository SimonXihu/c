#include <stdio.h>
#include <sys/types.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>

void my_func(int sig)
{
	switch(sig)
	{
		case 10:
			printf("Child process recv SIGUSR1,sig = %d,pid = %d\n",sig,getpid());
			break;
		case 12:
			printf("Father process recv SIGUSR2,sig = %d,pid = %d\n",sig,getpid());
			break;
		default:
			break;
	}
}
int main(void)
{
	pid_t pid = -1;
	//	signal(SIGUSR1,my_fuc);
	//	signal(SIGUSR2,my_fuc);
	pid = fork();
	if(pid == 0)
	{
		//signal(SIGUSR1,my_fuc);
		struct sigaction act_c;
		bzero(&act_c,sizeof(act_c));
		act_c.sa_handler = my_func;
		act_c.sa_flags = 0;
		sigaction(SIGUSR1,&act_c,NULL);
		sleep(1);
		while(1)
		{
			sleep(5);	
			kill(getppid(),SIGUSR2);
		}
	}
	else if(pid > 0)
	{
		//signal(SIGUSR2,my_fuc);
		struct sigaction act_f;
		bzero(&act_f,sizeof(act_f));
		act_f.sa_handler = my_func;
		act_f.sa_flags = 0;
		sigaction(SIGUSR2,&act_f,NULL);
	}
	else
	{
		perror("fork");
	}
	while(1)
	{
		sleep(5);
		kill(pid,SIGUSR1);	
	}
	return 0;
}
