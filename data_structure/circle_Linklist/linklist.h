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

typedef int (*COMPARE_LINKNODE)(LinkNode* n1,LinkNode* n2);
typedef void (*PRINT_LINKNODE)(LinkNode* node);

//init 
LinkList* init_circle_linklist(void);

//destroy
int destroy_circle_linklist(LinkList* list);

//insert
int insert_param_from_circle_linklist(LinkList* list,LinkNode* node,int pos);

//delete
int delete_param_from_circle_linklist(LinkList* list,LinkNode* node,COMPARE_LINKNODE compare);

//clear
int clear_circle_linklist(LinkList* list);

//print
void print_circle_linklist(LinkList *list,PRINT_LINKNODE print);
#endif