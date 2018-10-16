#include <stdio.h>
#include <string.h>
#include "linklist.h"

typedef struct PERSON
{
	LinkNode node;
	char name[64];
	int age;
}Person;

void print_person(LinkNode* per)
{
	Person* p = (Person*)per;
	printf("name:%s,age:%d\n",p->name,p->age);
}

int compare_person(LinkNode* node1,LinkNode* node2)
{
	Person* p1 = (Person*)node1;
	Person* p2 = (Person*)node2;
	if(p1->age == p2->age
		&& strcmp(p1->name,p2->name) == 0)
	{
		return 0;
	}
}

void test01()
{
	LinkList* list = init_Linklist();
	Person p1;
	p1.node.next = NULL;
	strcpy(p1.name,"aaaa");
	p1.age = 1;
	insert_param_from_Linklist(list,(LinkNode *)&p1,0);
	Person p2;
	p2.node.next = NULL;
	strcpy(p2.name,"bbbb");
	p2.age = 2;
	insert_param_from_Linklist(list,(LinkNode *)&p2,0);
	Person p3;
	p3.node.next = NULL;
	strcpy(p3.name,"cccc");
	p3.age = 3;
	insert_param_from_Linklist(list,(LinkNode *)&p3,0);
	Person p4;
	p4.node.next = NULL;
	strcpy(p4.name,"dddd");
	p4.age = 4;
	insert_param_from_Linklist(list,(LinkNode *)&p4,0);
	Person p5;
	p5.node.next = NULL;
	strcpy(p5.name,"eeee");
	p5.age = 5;
	insert_param_from_Linklist(list,(LinkNode *)&p5,0);
	Person p6;
	p6.node.next = NULL;
	strcpy(p6.name,"ffff");
	p6.age = 6;
	insert_param_from_Linklist(list,(LinkNode *)&p6,0);
	Person p7;
	p7.node.next = NULL;
	strcpy(p7.name,"gggg");
	p7.age = 7;
	insert_param_from_Linklist(list,(LinkNode *)&p7,0);
	print_Linklist(list,print_person);
	printf("--------------------------------\n");
	delete_param_from_Linklist(list,(LinkNode *)&p3,compare_person);
	delete_param_from_Linklist(list,(LinkNode *)&p1,compare_person);
	delete_param_from_Linklist(list,(LinkNode *)&p7,compare_person);
	print_Linklist(list,print_person);
	
	clear_LinkList(list);
	printf("--------------------------------\n");
	insert_param_from_Linklist(list,(LinkNode *)&p7,0);
	insert_param_from_Linklist(list,(LinkNode *)&p6,0);
	print_Linklist(list,print_person);
	free_linklist(list);
}
int main(int argc,char* argv[])
{
	printf("-----single linklist test_main-----\n");
	test01();
	return 0;
}