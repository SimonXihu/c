#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>
#include <unistd.h>

#define SERVER_PORT 6666
#define SERVER_IP "192.168.245.130"

int main(int argc,char * argv[])
{
	int sockfd=-1;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd == -1)
	{
		perror("socket");
	}
	
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr);
	
	int len;
	char bufr[BUFSIZ];
	char bufw[BUFSIZ];
	while(1)
	{
		bzero(bufr,sizeof(bufr));
		len = read(STDIN_FILENO,bufr,sizeof(bufr));
		if(len == -1)
		{
			perror("read");
		}
		len = sendto(sockfd,bufr,len,0,(struct sockaddr*)&server_addr,sizeof(server_addr));
		if(len == -1)
		{
			perror("sendto");
		}
		
		bzero(bufw,sizeof(bufw));
		len = recvfrom(sockfd,bufw,sizeof(bufw),0,NULL,0);
		if(len == -1)
		{
			perror("recvfrom");
		}
		printf("%s",bufw);
	}
	close(sockfd);
	return 0;
}