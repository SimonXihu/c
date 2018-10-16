#include "list.h"
#include <stdio.h>

typedef struct KEY2INDEX
{
	LinkNode head;
	unsigned int l2vpn_id;
	unsigned int peer_ip;
	unsigned int vc_id;
	unsigned int mpls_index;
}Key2Index;

int mycompare(LinkNode* node1,LinkNode* node2)
{
	Key2Index* n1 = (Key2Index*)node1;
	Key2Index* n2 = (Key2Index*)node2;
	if(n1->l2vpn_id == n2->l2vpn_id
		&& n1->peer_ip == n2->peer_ip
		&& n1->vc_id == n2->vc_id)
	{
		return 0;
	}
	else
	{
		return -1;
	}	
}

void linkprint(LinkNode* node)
{
	Key2Index* n = (Key2Index*)node;
	printf("-------------------\n");
	printf("l2vpn_id  :%u\n",n->l2vpn_id);
	printf("peer_ip   :%u\n",n->peer_ip);
	printf("vc_id     :%u\n",n->vc_id);
	printf("mpls_index:%u\n",n->mpls_index);
}
void test01()
{
	printf("***test01*****\n");
	LinkList* list = init_LinkList();
	if(list == NULL)
	{
		printf("init_LinkList error");
	}
	Key2Index k1,k2,k3,k4,k5;
	k1.l2vpn_id = 1;
	k2.l2vpn_id = 2;
	k3.l2vpn_id = 3;
	k4.l2vpn_id = 4;
	k5.l2vpn_id = 5;
	k1.peer_ip = 1;
	k2.peer_ip = 2;
	k3.peer_ip = 3;
	k4.peer_ip = 4;
	k5.peer_ip = 5;
	k1.vc_id = 1;
	k2.vc_id = 2;
	k3.vc_id = 3;
	k4.vc_id = 4;
	k5.vc_id = 5;
	k1.mpls_index = 1;
	k2.mpls_index = 2;
	k3.mpls_index = 3;
	k4.mpls_index = 4;
	k5.mpls_index = 5;
	int ret = add_Link_Node(list,(LinkNode*)&k5,0);
	if(ret == 0)
	{
		printf("add k5 ok\n");
	}
	ret  = add_Link_Node(list,(LinkNode*)&k4,0);
	if(ret == 0)
	{
		printf("add k4 ok\n");
	}
	ret = add_Link_Node(list,(LinkNode*)&k3,0);
	if(ret == 0)
	{
		printf("add k3 ok\n");
	}
	ret = add_Link_Node(list,(LinkNode*)&k2,0);
	if(ret == 0)
	{
		printf("add k2 ok\n");
	}
	ret = add_Link_Node(list,(LinkNode*)&k1,0);
	if(ret == 0)
	{
		printf("add k1 ok\n");
	}

	LinkList_print(list,linkprint);
	printf("***************************\n");	
	del_Link_Node(list,(LinkNode*)&k5,mycompare);	
	LinkList_print(list,linkprint);	
	printf("***************************\n");	
	ret = find_Link_Node(list,(LinkNode*)&k4,mycompare);
	if(ret != -1)
	{
		printf("find,pos=%d\n",ret);
	}
	else
	{
		printf("not find,ret=%d\n",ret);
	}
	free_LinkList(&list);
}
int main(int argc,char* argv[])
{
	test01();
	return 0;
}
