#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"

LinkList* init_Linklist(void)
{
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	if(list == NULL)
	{
		return NULL;
	}
	memset(list,0,sizeof(LinkList));
	list->length = 0;
	list->header.next = NULL;
	return list;
}

int insert_param_from_Linklist(LinkList *list,LinkNode *node,int pos)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	if(pos < 0 || pos > list->length)
	{
		pos = list->length;
	}
	int count = 0;
	LinkNode *tmp = (LinkNode *)(&(list->header));
	while(count < pos)
	{
		tmp = tmp->next;
		count++;
	}
	node->next = tmp->next;
	tmp->next = node;
	list->length++;
	return 0;
}

int delete_param_from_Linklist(LinkList *list,LinkNode *node,COMPARE_LINKNODE compare)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	int count = 0;
	LinkNode* pre = (LinkNode*)(&(list->header));
	LinkNode* current = pre->next;
	while(count < list->length)
	{
		if(compare(current,node) == 0)
		{
			pre->next = current->next;
			list->length--;
			break;
		}
		pre = pre->next;
		current = pre->next;
		count++;
	}
	if(count == list->length)
	{
		return -1;
	}
	return 0;
}

void print_Linklist(LinkList *list,PRINT_LINKLIST print)
{
	if(list == NULL)
	{
		return;
	}
	int count = 0;
	LinkNode *tmp_node = (LinkNode *)(&(list->header));
	for(;count < list->length;count++)
	{
		print(tmp_node->next);
		tmp_node = tmp_node->next;
	}
}

int free_linklist(LinkList *list)
{
	if(list == NULL)
	{
		return -1;
	}
	free(list);
	return 0;
}

int clear_LinkList(LinkList *list)
{
	if(list == NULL)
	{
		return -1;
	}
	list->length = 0;
	memset(list,0,sizeof(LinkList));
}