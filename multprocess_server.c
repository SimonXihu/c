#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#define SERVER_PORT 6666
int fd[1024];

void father_handle(int arg)
{
	int status;
	int ret;
	while((ret = waitpid(-1,&status,WNOHANG))!=-1)
	{
		if(ret == 0)
		{
			continue;
		}
		else
		{
			if(WIFEXITED(status))
			{
				printf("exit status: %d\n",WEXITSTATUS(status));
			}
			if(WIFSIGNALED(status))
			{
				printf("sig status: %d\n",WTERMSIG(status));
			}
			printf("child pid=%d\n",ret);
		}
	}
	return;
}
int main(void)
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int opt = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	int ret = bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(sockfd == -1)
	{
		perror("bind");
		return -1;
	}	
	listen(sockfd,128);
	memset(fd,-1,sizeof(fd));
	int connfd=-1;
	struct sockaddr_in client_addr;
	int client_addr_len = 0;
	bzero(&client_addr,sizeof(client_addr));
	int len=0;
	char bufr[BUFSIZ];
	char bufw[BUFSIZ];
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_handler = father_handle;
	act.sa_flags = 0;
	sigaction(SIGCHLD,&act,NULL);
	pid_t pid;
	while(1)
	{
		connfd = accept(sockfd,(struct sockaddr*)&client_addr,&client_addr_len);
		printf("aaaaaaaaaaaa\n");
		pid=fork();
		if(pid == 0)
		{
			//子进程
			printf("子进程");
			close(sockfd);
			while(1)
			{
				bzero(bufr,sizeof(bufr));
				bzero(bufw,sizeof(bufw));
				len = read(connfd,bufr,sizeof(bufr));
				if(len==0)
				{
					//客户端关闭
					printf("client closed\n");
					break;
				}
				if(len == -1)
				{
					break;
				}
				printf("receive client:%s\n",bufr);
				int j=0;
				for(j=0;j<len;j++)
				{
					bufw[j]=toupper(bufr[j]);
				}
				write(connfd,bufw,len);
			}
			close(connfd);
			break;
		}
		else if(pid > 0)
		{
			//父进程
			printf("父进程");
			if(connfd == -1)
			{
				continue;
			}
			close(connfd);
			char buf_addr[32];
			printf("receive connected:client_addr=%s,port=%hd\n",
					inet_ntop(AF_INET,
								&client_addr.sin_addr.s_addr,buf_addr,
								sizeof(buf_addr)),
					ntohs(client_addr.sin_port));
		}
		else
		{
			exit(0);
		}
		
	}
	close(sockfd);
	return 0;
}