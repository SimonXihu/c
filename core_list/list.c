#include "list.h"
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

LinkList* init_LinkList(void)
{
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	bzero(list,sizeof(LinkList));
	list->head.next = (LinkNode*)&(list->head);
	list->size = 0;
	return list;
}

int free_LinkList(LinkList** list)
{
	if(list == NULL)
	{
		return -1;
	}
	if(*list != NULL)
	{
		free(*list);
		*list = NULL;
		return 0;
	}
	else
	{
		return -1;
	}
}

int add_Link_Node(LinkList* list,LinkNode *node,int pos)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	if(pos < 0 || pos > list->size)
	{
		pos = list->size;
	}
	LinkNode *ptr = (LinkNode*)&(list->head);
	int i = 0;
	for(i = 0;i < pos;i++)
	{
		ptr = ptr->next;
	}

	node->next = ptr->next;
	ptr->next = node;
	list->size++;
	return 0;
}

int del_Link_Node(LinkList* list,LinkNode* node,MYCOMPARE compare)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	LinkNode* ptr1 = (LinkNode*)&(list->head);
	LinkNode* ptr2 = ptr1->next;
	int i = 0;
	for(i = 0;i < list->size;i++)
	{
		if(compare(ptr2,node) == 0)
		{
			ptr1->next = ptr2->next;
			list->size--;
			return 0;
		}
		ptr1 = ptr1->next;
		ptr2 = ptr1->next;
	}
	return -1;
}

int find_Link_Node(LinkList* list,LinkNode* node,MYCOMPARE compare)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	int i = 0;
	LinkNode* ptr = (LinkNode*)list->head.next;
	for(i = 0;i < list->size;i++)
	{
		if(compare(ptr,node) == 0)
		{
			return i+1;
		}
		ptr = ptr->next;
	}
	return -1;
}

void LinkList_print(LinkList *list,LinkPrint linkprint)
{
	if(list == NULL)
	{
		return;
	}
	int i = 0;
	LinkNode* tmp = (LinkNode*)list->head.next;
	for(i = 0;i < list->size;i++)
	{
		linkprint(tmp);
		tmp = tmp->next;
	}
}
