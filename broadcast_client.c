#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 8000   
#define CLIENT_PORT 9000

int main(int argc,char* argv[])
{
	int sockfd = -1;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(CLIENT_PORT);
	inet_pton(AF_INET,"0.0.0.0",&client_addr.sin_addr.s_addr);
	
	int ret;
	ret = bind(sockfd,(struct sockaddr*)&client_addr,sizeof(client_addr));
	if(ret == -1)
		perror("bind");
	char buf[BUFSIZ];
	while(1)
	{
		bzero(buf,sizeof(buf));
		recvfrom(sockfd,buf,sizeof(buf),0,NULL,0);
		printf("recv msg:%s",buf);
	}
	return 0;
}