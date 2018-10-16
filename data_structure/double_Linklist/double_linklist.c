#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double_linklist.h"

//init
LinkList* init_double_linklist(void)
{
	LinkList* list = (LinkList*)malloc(sizeof(LinkList));
	if(list == NULL)
	{
		return NULL;
	}
	memset(list,0,sizeof(LinkList));
	list->length = 0;
	list->head.prev = NULL;
	list->head.next = NULL;
	list->rear.prev = NULL;
	list->rear.next = NULL;
	return list;
}

//detroy
int destroy_double_linklist(LinkList* list)
{
	if(list == NULL)
	{
		return -1;
	}
	free(list);
	return 0;
}

//insert
int insert_param_from_double_linklist(LinkList* list,LinkNode* node,int pos)
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
	LinkNode *tmp_node = (LinkNode *)list->head.next;
	
	//头结点情况(还没有其他节点)
	if(tmp_node == NULL)
	{
		list->head.next = node;
		node->prev = (LinkNode *)&(list->head);
		node->next = NULL;
		list->length++;
		return 0;
	}
	
	tmp_node = (LinkNode *)&(list->head);
	while(count < pos)
	{
		tmp_node = tmp_node->next;
		count++;
	}
	
	//在尾部插入节点的情况
	if(pos == list->length)
	{
		tmp_node->next = node;
		node->prev = tmp_node;
		node->next = NULL;
		list->length++;
		return 0;
	}
	
	//其他情况
	LinkNode *next = tmp_node->next;
	
	node->next = tmp_node->next;
	tmp_node->next = node;
	node->prev = tmp_node;
	if(next != NULL)
	{
		next->prev = node;
	}
	list->length++;
	
	return 0;
}

//clear
int clear_double_linklist(LinkList* list)
{
	if(list == NULL)
	{
		return -1;
	}
	memset(list,0,sizeof(LinkList));
	list->length = 0;
	list->head.prev = NULL;
	list->head.next = NULL;
	list->rear.prev = NULL;
	list->rear.next = NULL;
	return 0;
}

//delete
int delete_param_from_double_linklist(LinkList* list,LinkNode* node,COMPARE_LINKNODE compare_linknode)
{
	if(list == NULL || node == NULL)
	{
		return -1;
	}
	
	int count = 0;
	LinkNode *pcur = (LinkNode *)&(list->head);
	LinkNode *pdel = pcur->next;
	if(pdel == NULL)
	{
		return -1;
	}
	while(count < list->length)
	{
		if(compare_linknode(pdel,node) == 0)
		{
			pcur->next = pdel->next;
			LinkNode *pnext = pdel->next;
			if(pnext != NULL)
			{
				pnext->prev = pcur;
			}
			list->length--;
			break;
		}
		pcur = pcur->next;
		pdel = pcur->next;
		count++;
	}
	if(count == list->length)
	{
		return -1;
	}
	return 0;
}

//print
void print_double_linklist(LinkList* list,PRINT_LINKNODE print_linknode)
{
	if(list == NULL)
	{
		return;
	}
	int count = 0;
	LinkNode *tmp_node = (LinkNode *)list->head.next;
	if(tmp_node == NULL)
	{
		return;
	}
	while(count < list->length)
	{
		print_linknode(tmp_node);
		tmp_node = tmp_node->next;
		count++;
	}
}