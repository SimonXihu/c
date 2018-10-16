#include "list.h"
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

LinkList* init_LinkList(void)
{
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	if(list == NULL)
	{
		perror("list init_LinkList");
		return NULL;
	}
	bzero(list,sizeof(LinkList));
	LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));
	if(node == NULL)
	{
		perror("node init_LinkList");
		return NULL;
	}
	bzero(node,sizeof(LinkNode));
	list->node = node;
	node->next = NULL;
	list->size = 0;
	return list;
}

int add_LinkNode(LinkList* list,LinkNode* node,int pos)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	if(pos < 0 || pos > list->size)
	{
		pos = list->size;
	}
	int i = 0;
	LinkNode* ptr = list->node->next;
	for(i = 0;i < pos;i++)
	{
		ptr = ptr->next;
	}
	node->next = ptr->next;
	ptr->next = node;
	list->size++;
	return 0;
}

int del_LinkNode(LinkList* list,LinkNode* node,COMPARE compare)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	int i = 0;
	LinkNode* ptr1 = list->node;
	LinkNode* ptr2 = ptr1->next;
	for(i = 0;i < list->size;i++)
	{
		if(compare(ptr1,node) == 0)
		{
			ptr1->next = ptr2->next;
			free(ptr2);
			list->size--;
			return 0;
		}
		ptr1 = ptr1->next;
		ptr2 = ptr1->next;
	}
	return -1;
}

void LinkList_print(LinkList* list,LINKLIST_PRINT linklist_print)
{
	LinkNode* ptr = list->node->next;
	int i =0;
	for(i = 0;i < list->size;i++)
	{
		linklist_print(ptr);
	}
}
