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
	int sockfd=-1;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd == -1)
		perror("socket");
	
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int ret;
	ret = bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret == -1)
		perror("bind");
	
	int flag = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,&flag,sizeof(flag));
	
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(CLIENT_PORT);
	inet_pton(AF_INET,"192.168.245.255",&client_addr.sin_addr.s_addr);
	int len;
	char bufw[BUFSIZ];
	while(1)
	{
		bzero(bufw,sizeof(bufw));
		len = read(STDIN_FILENO,bufw,sizeof(bufw));
		len = sendto(sockfd,bufw,len,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
		if(len == -1)
			perror("sendto");
	}
	return 0;
}