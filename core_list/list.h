#ifndef _LIST_H_
#define _LIST_H_

typedef struct LINKNODE
{
	struct LINKNODE* next;
}LinkNode;

typedef struct LINKLIST
{
	LinkNode head;
	int size;
}LinkList;

typedef int (*MYCOMPARE)(LinkNode* node1,LinkNode* node2);
typedef void (*LinkPrint)(LinkNode* node);

//初始化
LinkList* init_LinkList(void);

//free
int free_LinkList(LinkList** list);

//add LinkNode
int add_Link_Node(LinkList* list,LinkNode *node,int pos);

//del LinkNode
int del_Link_Node(LinkList* list,LinkNode* node,MYCOMPARE compare);

//find
int find_Link_Node(LinkList* list,LinkNode* node,MYCOMPARE compare);

//print
void LinkList_print(LinkList *list,LinkPrint linkprint);
#endif
