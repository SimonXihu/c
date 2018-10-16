#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <sys/un.h>
#include <unistd.h>
#include <ctype.h>

#define SERVER_ADDR "@server.sock"
#define CLIENT_ADDR "@client.sock"

int main(int argc,char* argv[])
{
	int sockfd=-1;
	sockfd = socket(AF_UNIX,SOCK_STREAM,0);
	if(sockfd == -1)
		perror("socket");
	
	struct sockaddr_un server_un;
	server_un.sun_family = AF_UNIX;
	strcpy(server_un.sun_path,SERVER_ADDR);
	
	int len;
	len = offsetof(struct sockaddr_un,sun_path)+strlen(server_un.sun_path);
	server_un.sun_path[0]='\0';
	
	int ret;
	unlink(SERVER_ADDR);
	ret = bind(sockfd,(struct sockaddr*)&server_un,len);
	if(ret == -1)
		perror("bind");
	
	listen(sockfd,128);
	printf("--------accept-------\n");
	
	int connfd;
	struct sockaddr_un client_un;
	socklen_t client_un_len=sizeof(client_un);
	
	char buf[BUFSIZ];
	int i=0;
	char bufw[BUFSIZ];
	while(1)
	{
		connfd = accept(sockfd,(struct sockaddr*)&client_un,&client_un_len);
		if(connfd == -1)
			perror("accept");
		len = client_un_len - offsetof(struct sockaddr_un,sun_path);
		client_un.sun_path[0] = '@';
		printf("client sun_path:%s\n",client_un.sun_path);
		
		bzero(buf,sizeof(buf));
		while((len = read(connfd,buf,sizeof(buf)))!=-1)
		{
			if(len == -1)
				perror("read");
			printf("recv client msg:%s\n",buf);
			
			bzero(bufw,sizeof(bufw));
			for(i=0;i<len;i++)
				bufw[i]=toupper(buf[i]);
			
			len = write(connfd,bufw,sizeof(bufw));
			if(len == -1)
				perror("write");
		}
		close(connfd);
	}
	
	close(sockfd);
	
	return 0;
}