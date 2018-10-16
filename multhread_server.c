#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

#define SERVER_PORT 6666
#define MAX_THREAD 32

int fds[MAX_THREAD];

void* accept_client(void* arg)
{
	int* j = (int *)arg;
	int fd = fds[*j];
	int len=0;
	char bufr[BUFSIZ];
	char bufw[BUFSIZ];
	int i=0;
	printf("BUFSIZ=%d\n",BUFSIZ);
	while(1)
	{
		bzero(bufr,sizeof(bufr));
		bzero(bufw,sizeof(bufw));
		len = read(fd,bufr,sizeof(bufr));
		if((len==-1)||(len==0))
		{
			close(fd);
			fds[*j]=-1;
			printf("client closed\n");
			pthread_exit(0);
		}
		printf("receive client:%s\n",bufr);
		
		for(i=0;i<len;i++)
		{
			bufw[i]=toupper(bufr[i]);
		}
		printf("write to client:%s\n",bufw);
		write(fd,bufw,len);
	}
}

int main(void)
{
	pthread_t thread[1024];
	int tmp = 0;
	int fdnum[MAX_THREAD];
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in server_addr;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int opt = 1;
	setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	int ret = bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		perror("bind");
		return -1;
	}
	listen(sockfd,128);
	int connfd=-1;
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	int client_addr_len = 0;
	
	memset(fds,-1,sizeof(fds));
	void* arg;
	char buf_addr[32];
	while(1)
	{
		connfd = accept(sockfd,(struct sockaddr*)&client_addr,&client_addr_len);
		printf("receive connected:client_addr=%s,port=%hd\n",
					inet_ntop(AF_INET,
								&client_addr.sin_addr.s_addr,buf_addr,
								sizeof(buf_addr)),
					ntohs(client_addr.sin_port));
		int j=0;
		for(j=0;j<MAX_THREAD;j++)
		{
			if(fds[j] == -1)
			{
				fds[j]=connfd;
				fdnum[j]=j;
				arg =(void*)(fdnum+j);
				pthread_create(&thread[tmp],NULL,accept_client,arg);
				pthread_detach(thread[tmp]);
				tmp++;
				break;
			}
		}
	}
}