#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>
#include <unistd.h>

#define SERVER_PORT 6666

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
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret == -1)
	{
		perror("bind");
	}
	
	int len = 0;
	int i = 0;
	char bufr[BUFSIZ];
	char bufw[BUFSIZ];
	
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	socklen_t client_addr_len=sizeof(client_addr);
	char clientip[INET_ADDRSTRLEN];
	bzero(clientip,sizeof(clientip));
	
	printf("----wait for connect----\n");
	while(1)
	{
		bzero(bufr,BUFSIZ);
		len = recvfrom(sockfd,bufr,sizeof(bufr),0,(struct sockaddr*)&client_addr,&client_addr_len);
		if(len == -1)
		{
			perror("recvfrom");
		}
		printf("client addr:%s,client port:%d,client msg:%s",
				inet_ntop(AF_INET,&client_addr.sin_addr,clientip,sizeof(clientip)),
				ntohs(client_addr.sin_port),
				bufr);
				
		bzero(bufw,BUFSIZ);
		for(i=0;i<len;i++)
		{
			bufw[i]=toupper(bufr[i]);
		}
		printf("send to client msg:%s",bufw);
		
		len = sendto(sockfd,bufw,len,0,(struct sockaddr*)&client_addr,client_addr_len);
		if(len == -1)
		{
			perror("sendto");
		}
	}
	close(sockfd);
	
	return 0;
}