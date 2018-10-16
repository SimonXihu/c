#ifndef _DOUBLE_LINKLIST_H_
#define _DOUBLE_LINKLIST_H_

typedef struct LINKNODE
{
	void* data;
	struct LINKNODE* prev;
	struct LINKNODE* next;
}LinkNode;

typedef struct LINKLIST
{
	LinkNode head;
	LinkNode rear;
	int length;
}LinkList;

typedef int (*COMPARE_LINKNODE)(LinkNode* n1,LinkNode* n2);
typedef void (*PRINT_LINKNODE)(LinkNode* n);

//init
LinkList* init_double_linklist(void);

//detroy
int destroy_double_linklist(LinkList* list);

//insert
int insert_param_from_double_linklist(LinkList* list,LinkNode* node,int pos);

//clear
int clear_double_linklist(LinkList* list);

//delete
int delete_param_from_double_linklist(LinkList* list,LinkNode* node,COMPARE_LINKNODE compare_linknode);

//print
void print_double_linklist(LinkList* list,PRINT_LINKNODE print_linknode);

#endif