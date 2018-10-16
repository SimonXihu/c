#include <stdio.h>
#include "vector.h"

void test01()
{
	vector* vec = init_vector();
	int i = 1;
	for(;i <= 30;i++)
	{
		insert_param_to_vector(vec,-1,i);
	}
	print_vector(vec);
}
int main(int argc,char* argv[])
{
	printf("----------vector test_main----------\n");
	test01();
	return 0;
}