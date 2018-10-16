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
#define SERVER_IP "192.168.245.130"

int main(void)
{
	char buf[1024];
	char bufr[1024];
	int len=0;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket:");
		return -1;
	}
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(sockfd,SERVER_IP,&server_addr.sin_addr.s_addr);
	int ret = connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	printf("connect ok\n");
	if(ret == -1)
	{
		perror("connect:");
		return -1;
	}
	while(1)
	{
		bzero(buf,sizeof(buf));
		bzero(bufr,sizeof(bufr));
		//屏幕输入
		len=read(0,buf,sizeof(buf));
		//发送给服务器
		write(sockfd,buf,len);
		//从服务器读
		len = read(sockfd,bufr,sizeof(bufr));
		//printf("len = %d\n",len);
		printf("%s\n",bufr);
	}
	close(sockfd);
	return 0;
}