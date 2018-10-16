#include <signal.h>
#include <stdio.h>

void myfunc(int sig)
{
	printf("ctrl+c\n");
}
int main(void)
{
	struct sigaction act;
	act.sa_handler = myfunc;
	act.sa_flags = 0;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGQUIT);
	sigprocmask(SIG_BLOCK,&set,NULL);

	sigaction(SIGINT,&act,NULL);
	while(1)
	{
	}
	return 0;
}
