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

	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(CLIENT_PORT);
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret;
	ret = bind(sockfd,(struct sockaddr*)&client_addr,sizeof(client_addr));

	struct ip_mreqn group;
	bzero(&group,sizeof(group));
	inet_pton(AF_INET,GROUP,&group.imr_multiaddr.s_addr);
	inet_pton(AF_INET,"0.0.0.0",&group.imr_address.s_addr);
	group.imr_ifindex=if_nametoindex("ens33");
	setsockopt(sockfd,IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group));

	int len;
	char buf[BUFSIZ];
	while(1)
	{
		bzero(buf,sizeof(buf));
		len = recvfrom(sockfd,buf,sizeof(buf),0,NULL,0);
		printf("recv msg:%s",buf);
	}
	return 0;
}
