#ifndef _LIST_H_
#define _LIST_H_

typedef struct LINKNODE
{
	void* data;
	struct LINKNODE* next;
}LinkNode;

typedef struct LINKLIST
{
	LinkNode* node;
	int size;
}LinkList;

typedef int (*COMPARE)(LinkNode* node1,LinkNode* node2);
typedef void (*LINKLIST_PRINT)(LinkNode* node);

LinkList* init_LinkList(void);

int add_LinkNode(LinkList* list,LinkNode* node,int pos);

int del_LinkNode(LinkList* list,LinkNode* node,COMPARE compare);

void LinkList_print(LinkList* list,LINKLIST_PRINT linklist_print);

#endif
