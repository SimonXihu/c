#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_FDS 1024
#define SERVER_PORT 6666

int main(void)
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	char buf_addr[32];
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
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	int ret = bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}
	listen(sockfd,128);

	struct pollfd fds[MAX_FDS],fds_r[MAX_FDS];
	nfds_t nfds=0;
	int nready=-1;
	memset(fds,-1,sizeof(fds));
	memset(fds_r,-1,sizeof(fds_r));
	fds[0].fd = sockfd;
	fds[0].events = POLLIN;

	int connfd=-1;
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	int client_addr_len=0;
	while(1)
	{
		memset(fds_r,-1,sizeof(fds_r));
		memcpy(fds_r,fds,sizeof(fds));

		nready=poll(fds_r,nfds+1,-1);
		if(fds_r[0].revents == POLLIN)
		{
			connfd=accept(sockfd,(struct sockaddr*)&client_addr,&client_addr_len);
			if(connfd == -1)
			{
				perror("accept");
			}
			else
			{
				printf("receive connected:client_addr=%s,port=%hd\n",
						inet_ntop(AF_INET,
							&client_addr.sin_addr.s_addr,buf_addr,
							sizeof(buf_addr)),
						ntohs(client_addr.sin_port));
				int i=0;
				for(i=0;i<MAX_FDS;i++)
				{
					if(fds[i].fd == -1)
					{
						fds[i].fd = connfd;
						fds[i].events = POLLIN;
						if(nfds<i)
						{
							nfds=i;
						}
						break;
					}
				}
				nready--;
				if(nready == 0)
				{
					continue;
				}
			}
		}
		int j=1;
		for(j=1;j<nfds+1;j++)
		{
			if(fds_r[j].revents == POLLIN)
			{
				int len;
				char bufr[1024];
				char bufw[1024];
				bzero(bufr,sizeof(bufr));
				bzero(bufw,sizeof(bufw));
				len = read(fds_r[j].fd,bufr,sizeof(bufr));
				printf("client:%s\n",bufr);
				if(len == -1)
				{
					perror("read");
					close(fds_r[j].fd);
					fds_r[j].fd=-1;
				}
				else if(len == 0)
				{
					close(fds_r[j].fd);
					fds_r[j].fd=-1;
				}
				int i=0;
				for(i=0;i<len;i++)
				{
					bufw[i]=toupper(bufr[i]);
				}
				len = write(fds_r[j].fd,bufw,sizeof(bufw));
				nready--;
			}
			if(nready == 0)
			{
				break;
			}
		}
	}
	return 0;
}
