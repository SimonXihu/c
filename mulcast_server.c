#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>

#if 0
struct ip_mreqn {
        struct in_addr  imr_multiaddr;          /* IP multicast address of group */
        struct in_addr  imr_address;            /* local IP address of interface */
        int             imr_ifindex;            /* Interface index */
};
/* Internet address. */
struct in_addr {
        __be32  s_addr;
};
#endif

#define SERVER_PORT 8000
#define CLIENT_PORT 9000

#define GROUP "239.0.0.2"

int main(int argc,char* argv[])
{
	int sockfd = -1;
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
	
	struct ip_mreqn group;
	bzero(&group,sizeof(group));
	inet_pton(AF_INET,GROUP,&group.imr_multiaddr.s_addr);
	inet_pton(AF_INET,"0.0.0.0",&group.imr_address.s_addr);
	group.imr_ifindex=if_nametoindex("ens33");
	//开组播权限
	setsockopt(sockfd,IPPROTO_IP, IP_MULTICAST_IF, &group, sizeof(group));
	
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(CLIENT_PORT);
	inet_pton(AF_INET,GROUP,&client_addr.sin_addr.s_addr);
	
	int len;
	char buf[BUFSIZ];
	
	printf("--------------\n");
	while(1)
	{
		len = read(STDIN_FILENO,buf,sizeof(buf));
		if(len == -1)
			perror("read");
		len = sendto(sockfd,buf,len,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
		if(len == -1)
			perror("sendto");
	}
	return 0;
}