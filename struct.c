#include <stdio.h>


int g ;
//int g = 1;
struct student
{
	char name[64];
	int age;
};
f()
{
	printf("f()\n");
}
int main(void)
{
	struct student s1={"simon",25};
	//student s2={"abc",20};
	printf("g = %d\n",g);
	//f(1,2,3,4,51,2,3,4,51,2,3,4,51,2,3,4,51,2,3,4,5);
	f(10);
	const int x = 10;
	int array[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("sizeof(array)= %d",sizeof(array));	
	return 0;
}
