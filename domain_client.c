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
	
	struct sockaddr_un client_un;
	bzero(&client_un,sizeof(client_un));
	client_un.sun_family = AF_UNIX;
	strcpy(client_un.sun_path,CLIENT_ADDR);
	
	int len;
	len = offsetof(struct sockaddr_un,sun_path)+strlen(client_un.sun_path);
	client_un.sun_path[0]='\0';
	unlink(CLIENT_ADDR);
	int ret;
	ret = bind(sockfd,(struct sockaddr*)&client_un,len);
	if(ret == -1)
		perror("bind");

	struct sockaddr_un server_un;
	server_un.sun_family = AF_UNIX;
	strcpy(server_un.sun_path,SERVER_ADDR);
	len = offsetof(struct sockaddr_un,sun_path)+strlen(server_un.sun_path);
	server_un.sun_path[0]='\0';
	
	char bufr[BUFSIZ];
	char bufw[BUFSIZ];
	ret = connect(sockfd,(struct sockaddr*)&server_un,len);
		if(ret == -1)
			perror("connect");
	while(1)
	{
		bzero(bufr,sizeof(bufr));
		len = read(STDIN_FILENO,bufr,sizeof(bufr));
		if(len == -1)
			perror("read");
		
		len = write(sockfd,bufr,sizeof(bufr));
		if(len == -1)
			perror("write");
		
		bzero(bufw,sizeof(bufw));
		len = read(sockfd,bufw,sizeof(bufw));
		if(len == -1)
			perror("read");
		printf("%s\n",bufw);
	}
	return 0;
}