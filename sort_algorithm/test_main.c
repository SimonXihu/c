#include <stdio.h>
#include "sort_algorithm.h"

void print_arr(int *arr,int arr_length)
{
	int i = 0;
	for(i = 0;i < arr_length;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int main(int argc,char* argv[])
{
	printf("----------sort_algorithm:test_main----------\n");
	
	int *arr = NULL;
	create_arr(&arr);
	//print_arr(arr,ARRLENGTH);
	
	//Bubble_sort(arr,ARRLENGTH);
	
	//Select_sort(arr,ARRLENGTH);
	//Insert_sort(arr,ARRLENGTH);
	Shell_sort(arr,ARRLENGTH);
	//print_arr(arr,ARRLENGTH);
	
	//printf("sort ok\n");
	detroy_arr(&arr);
	return 0;
}