#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


#define SERVER_PORT 6666
#define MAX_FD 1024

int main(void)
{
	int tmp=0;
	int fd[MAX_FD];
	char buf_addr[32];
	char bufread[1024];
	char bufwrite[1024];
	int maxfd=-1;
	int len=0;
	memset(fd,-1,sizeof(fd));
	int fd_num=0;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	maxfd=sockfd;
	if(sockfd == -1)
	{
		perror("socket:");
		return -1;
	}
	int ret=0;
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	ret = bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		perror("bind:");
		return -1;
	}
	
	ret = listen(sockfd,128);
	if(ret == -1)
	{
		perror("listen:");
		return -1;
	}
	
	fd[0]=sockfd;
	int nready=-1;
	fd_set readfds1;
	fd_set readfds;
	FD_ZERO(&readfds1);
	FD_ZERO(&readfds);
	FD_SET(sockfd,&readfds1);
	
	int connfd=-1;
	
	struct sockaddr_in client_addr;
	int client_addr_len=0;
	bzero(&client_addr,sizeof(client_addr));
	printf("init server\n");
	while(1)
	{
		readfds=readfds1;
		nready=select(maxfd+1,&readfds,NULL,NULL,NULL);
		if(FD_ISSET(sockfd,&readfds))
		{
			printf("accept\n");
			connfd=accept(sockfd,(struct sockaddr*)&client_addr,&client_addr_len);
			if(connfd == -1)
			{
				perror("accept:");
			}
			else
			{
				for(tmp=0;tmp<MAX_FD;tmp++)
				{
					if(fd[tmp]==-1)
					{
						fd[tmp]=connfd;
						if(maxfd < connfd)
						{
							maxfd=connfd;
						}
						FD_SET(connfd,&readfds1);
						break;
					}
				}
				if(tmp == MAX_FD)
				{
					printf("up to MAX_FD");
					return -1;
				}
				
				printf("receive connected:client_addr=%s,port=%hd\n",
					inet_ntop(AF_INET,
								&client_addr.sin_addr.s_addr,buf_addr,
								sizeof(buf_addr)),
					ntohs(client_addr.sin_port));
					
				nready--;
				if(nready == 0)
				{
					continue;
				}
			}
		}
		

	
		for(tmp=1;tmp<MAX_FD;tmp++)
		{
			if(FD_ISSET(fd[tmp],&readfds))
			{
				len=read(fd[tmp],bufread,sizeof(bufread));
				if(len==-1)
				{
					perror("read:");
					fd[tmp]=-1;
					FD_CLR(fd[tmp],&readfds1);
					close(fd[tmp]);
					break;
				}
				else if(len==0)
				{
					printf("client closed fd\n");
					fd[tmp]=-1;
					FD_CLR(fd[tmp],&readfds1);
					close(fd[tmp]);
					break;
				}
				
				int mmm=0;
				
				for(mmm=0;mmm<len;mmm++)
				{
					bufwrite[mmm]=toupper(bufread[mmm]);
				}
				
				len=write(fd[tmp],bufwrite,len);
				
				nready--;
				if(nready == 0)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
	
	}
	return 0;
}