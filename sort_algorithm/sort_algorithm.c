#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sort_algorithm.h"


int create_arr(int **arr)
{
	int arr_length = ARRLENGTH;
	int i = 0;
	int *temp = (int *)malloc(sizeof(int) * arr_length);
	
	//设置随机数种子
	srand((unsigned int)time(NULL));
	for(i = 0;i < arr_length;i++)
	{
		temp[i] = rand() % 100;
	}
	
	*arr = temp;
	return 0;
}

//销毁随机数组
int detroy_arr(int **arr)
{
	if(*arr != NULL)
	{
		free(*arr);
		*arr = NULL;
		
		return 0;
	}
	
	return -1;
}
int Bubble_sort(int *arr,int arr_length)
{
	int i = 0,j = 0;
	int temp = 0;
	struct timespec tp_before,tp_end;
	double time = 0;
	
	//排序前的时间
	int ret = clock_gettime(CLOCK_REALTIME, &tp_before);
	if(ret != 0)
	{
		perror("Bubble_sort before");
		return -1;
	}

	//控制次数
	for(i = 0;i < arr_length;i++)
	{
		//比较
		for(j = 0;j < arr_length - i -1;j++)
		{
			//从小到大
			if(arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	
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

	printf("排序时间：%lf \n",time);
		
	return 0;
}