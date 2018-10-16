#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"

typedef struct PERSON
{
	LinkNode node;
	char name[64];
	int age;
}Person;

void print_person(LinkNode* node)
{
	Person *p = (Person*)node;
	printf("name:%s,age:%d\n",p->name,p->age);
}

int compare_person(LinkNode* n1,LinkNode* n2)
{
	Person* p1 = (Person*) n1;
	Person* p2 = (Person*) n2;
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
	Person p2;
	strcpy(p2.name,"bbbb");
	p2.age = 2;
	Person p3;
	strcpy(p3.name,"cccc");
	p3.age = 3;
	
	LinkList* list = init_circle_linklist();
	insert_param_from_circle_linklist(list,(LinkNode*) &p1,0);
	insert_param_from_circle_linklist(list,(LinkNode*) &p2,1);
	insert_param_from_circle_linklist(list,(LinkNode*) &p3,2);
	print_circle_linklist(list,print_person);
	printf("---------------------\n");
	clear_circle_linklist(list);
	insert_param_from_circle_linklist(list,(LinkNode*) &p2,1);
	insert_param_from_circle_linklist(list,(LinkNode*) &p3,2);
	insert_param_from_circle_linklist(list,(LinkNode*) &p1,0);
	print_circle_linklist(list,print_person);
	printf("---------------------\n");
	delete_param_from_circle_linklist(list,(LinkNode*) &p3,compare_person);
	print_circle_linklist(list,print_person);
}
int main(int argc,char* argv[])
{
	printf("-----circle linklist test main -----\n");
	test01();
	return 0;
}