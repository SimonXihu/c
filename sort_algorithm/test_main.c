#include <stdio.h>
#include <time.h>
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
	print_arr(arr,ARRLENGTH);
	
	//Bubble_sort(arr,ARRLENGTH);
	
	//Select_sort(arr,ARRLENGTH);
	//Insert_sort(arr,ARRLENGTH);
	//Shell_sort(arr,ARRLENGTH);
	
	#if 1 //快速排序
	struct timespec tp_before,tp_end;
	double time = 0;
	
	//排序前的时间
	int ret = clock_gettime(CLOCK_REALTIME, &tp_before);
	if(ret != 0)
	{
		perror("Bubble_sort before");
		return -1;
	}
	Quick_sort(arr,0,ARRLENGTH);
	
	//排序后的时间
	ret = clock_gettime(CLOCK_REALTIME, &tp_end);
	if(ret != 0)
	{
		perror("Bubble_sort end");
		return -1;
	}
	
	//排序时间
	time = (tp_end.tv_sec - tp_before.tv_sec) + 
		(tp_end.tv_nsec - tp_before.tv_nsec) / 1000000000.0;

	printf("快速排序排序时间：%lf \n",time);
	#endif
	print_arr(arr,ARRLENGTH);
	
	//printf("sort ok\n");
	detroy_arr(&arr);
	return 0;
}