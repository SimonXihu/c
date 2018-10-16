#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double_linklist.h"

typedef struct PERSON
{
	char name[64];
	int age;
}Person;

void print_person(LinkNode* node)
{
	Person *p = (Person*)node->data;
	printf("name:%s,age:%d\n",p->name,p->age);
}

int compare_person(LinkNode* n1,LinkNode* n2)
{
	Person* p1 = (Person*) n1->data;
	Person* p2 = (Person*) n2->data;
	if(p1->age == p2->age
		&& strcmp(p1->name,p2->name) == 0)
	{
		return 0;
	}
	return -1;
}

void test01()
{
	Person p1;
	strcpy(p1.name,"aaaa");
	p1.age = 1;
	LinkNode n1;
	n1.data = (void*)&p1;
	
	Person p2;
	strcpy(p2.name,"bbbb");
	p2.age = 2;
	LinkNode n2;
	n2.data = (void*)&p2;
	
	Person p3;
	strcpy(p3.name,"cccc");
	p3.age = 3;
	LinkNode n3;
	n3.data = (void*)&p3;
	
	LinkList* list = init_double_linklist();
	insert_param_from_double_linklist(list,(LinkNode *) &n1,0);
	insert_param_from_double_linklist(list,(LinkNode *) &n2,1);
	insert_param_from_double_linklist(list,(LinkNode *) &n3,2);
	print_double_linklist(list,print_person);
	printf("---------------------\n");
	clear_double_linklist(list);
	insert_param_from_double_linklist(list,(LinkNode *) &n1,-1);
	insert_param_from_double_linklist(list,(LinkNode *) &n2,-1);
	insert_param_from_double_linklist(list,(LinkNode *) &n3,-1);
	delete_param_from_double_linklist(list,(LinkNode*) &n3,compare_person);
	delete_param_from_double_linklist(list,(LinkNode*) &n1,compare_person);
	delete_param_from_double_linklist(list,(LinkNode*) &n2,compare_person);
	print_double_linklist(list,print_person);
	printf("---------------------\n");
	destroy_double_linklist(list);
}

int main(int argc,char* argv[])
{
	printf("-----double linklist test main -----\n");
	test01();
	return 0;
}