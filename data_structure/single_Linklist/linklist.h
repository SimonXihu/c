#ifndef _LINKLIST_H_
#define _LINKLIST_H_

typedef struct LINKNODE
{
	struct LINKNODE* next;
}LinkNode;

typedef struct LINKLIST
{
	LinkNode header;
	int length;
}LinkList;

typedef void (*PRINT_LINKLIST)(LinkNode* node);
typedef int (*COMPARE_LINKNODE)(LinkNode* node1,LinkNode* node2);

//init
LinkList* init_Linklist(void);

//insert
int insert_param_from_Linklist(LinkList *list,LinkNode *node,int pos);

//delete
int delete_param_from_Linklist(LinkList *list,LinkNode *node,COMPARE_LINKNODE compare);

//print
void print_Linklist(LinkList *list,PRINT_LINKLIST print);

//free
int free_linklist(LinkList *list);

//clear
int clear_LinkList(LinkList *list);
#endif