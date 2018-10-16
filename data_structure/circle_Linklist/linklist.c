#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"

//init 
LinkList* init_circle_linklist(void)
{
	LinkList *list = (LinkList *)malloc(sizeof(LinkList));
	if(list == NULL)
	{
		return NULL;
	}
	memset(list,0,sizeof(LinkList));
	list->header.next = (LinkNode*)&(list->header);
	list->length = 0;
	return list;
}

//destroy
int destroy_circle_linklist(LinkList* list)
{
	if(list == NULL)
	{
		return -1;
	}
	free(list);
	return 0;
}

//insert
int insert_param_from_circle_linklist(LinkList* list,LinkNode* node,int pos)
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
	LinkNode* tmp_node = (LinkNode*)&(list->header);
	while(count < pos)
	{
		tmp_node = tmp_node->next;
		count++;
	}
	
	node->next=tmp_node->next;
	tmp_node->next = node;
	list->length++;
	return 0;
}

//delete
int delete_param_from_circle_linklist(LinkList* list,LinkNode* node,COMPARE_LINKNODE compare)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	int count = 0;
	LinkNode* pre = (LinkNode*)&(list->header);
	LinkNode* current = pre->next;
	while(count < list->length)
	{
		if(compare(current,node) == 0)
		{
			pre->next = pre->next->next;
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

//clear
int clear_circle_linklist(LinkList* list)
{
	if(list == NULL)
	{
		return -1;
	}
	list->length = 0;
	return 0;
}

//print
void print_circle_linklist(LinkList *list,PRINT_LINKNODE print)
{
	if(list == NULL)
	{
		return;
	}
	int count = 0;
	LinkNode* tmp_node = (LinkNode*)list->header.next;
	while(count < list->length)
	{
		print(tmp_node);
		tmp_node = tmp_node->next;
		count++;
	}
}