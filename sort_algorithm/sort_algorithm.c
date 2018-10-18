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

//冒泡
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

	int Bubble_flag = true;
	
	//控制次数
	for(i = 0;(i < arr_length) && (Bubble_flag == true);i++)
	{
		Bubble_flag = false;
		
		//比较
		for(j = 0;j < arr_length - i -1;j++)
		{
			//从小到大
			if(arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				Bubble_flag = true;
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

	printf("冒泡排序时间：%lf \n",time);
		
	return 0;
}

//选择
int Select_sort(int *arr,int arr_length)
{
	int i = 0,j = 0;
	int min = -1;
	int temp  = 0;
	struct timespec tp_before,tp_end;
	double time = 0;
	
	//排序前的时间
	int ret = clock_gettime(CLOCK_REALTIME, &tp_before);
	if(ret != 0)
	{
		perror("Bubble_sort before");
		return -1;
	}
	
	for(i = 0;i < arr_length;i++)
	{
		min = i;
		for(j = i + 1;j < arr_length;j++)
		{
			//从小到大
			if(arr[min] > arr[j])
			{
				min  = j;
			}
		}
		if(min != i)
		{
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
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

	printf("选择排序时间：%lf \n",time);
	return 0;
}

//插入
int Insert_sort(int *arr,int arr_length)
{
	int i = 0,j = 0;
	int temp  = 0;
	struct timespec tp_before,tp_end;
	double time = 0;
	
	//排序前的时间
	int ret = clock_gettime(CLOCK_REALTIME, &tp_before);
	if(ret != 0)
	{
		perror("Bubble_sort before");
		return -1;
	}
	
	for(i = 1;i < arr_length;i++)
	{
		if(arr[i] < arr[i - 1])
		{
			temp = arr[i];
			for(j = i - 1;j >= 0 && temp < arr[j];j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;	
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

	printf("插入排序时间：%lf \n",time);
	return 0;
}

//希尔
int Shell_sort(int *arr,int arr_length)
{
	int increament = arr_length;
	int i = 0,j = 0,k = 0;
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
	
	while(increament > 1)
	{
		increament = increament/3 + 1;
		for(i = 0;i < increament;i++)
		{
			for(j = i + increament; j < arr_length;j = j + increament)
			{
				temp = arr[j];
				if(arr[j - increament] > temp)
				{
					for(k = j - increament; k >= 0 && arr[k] > temp;k = k - increament)
					{
						arr[k + increament] = arr[k];
					}
					arr[k + increament] = temp;
				}
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

	printf("希尔排序时间：%lf \n",time);
	return 0;
}

//快速排序(挖坑法)
int Quick_sort(int *arr,int arr_begin,int arr_length)
{
	int left = arr_begin;
	int right = arr_length;
	int target = arr[left];//左边第一个作为基准数
	
	if(left < right)
	{
		while(left < right)
		{
			//以左边第一个作为基准数，所以从右边开始找第一个比基准数小的
			while(left < right && arr[right] > target)
			{
				right--;
			}
			if(left < right)
			{
				arr[left] = arr[right];
				left++;
			}
			
			//然后从左边开始查找第一个比基准数大的
			while(left < right && arr[left] < target)
			{
				left++;
			}
			if(left < right)
			{
				arr[right] = arr[left];
				right--;
			}
		}
		
		//最后的位置放入基准数
		arr[left] = target;
		
		Quick_sort(arr,arr_begin,left - 1);
		Quick_sort(arr,left + 1,arr_length);
	}

	return 0;
}

//归并合并算法
int Merge(int *arr,int arr_begin,int arr_length,int mid,int *temp_arr)
{
	if(arr_begin >= arr_length)
	{
		return 0;
	}
	int i = 0;
	int i_start = arr_begin;
	int i_end = mid;
	int j_start = mid + 1;
	int j_end = arr_length;
	int length = 0;
	while(i_start <= i_end && j_start <=j_end)
	{
		if(arr[i_start] < arr[j_start])
		{
			temp_arr[length] = arr[i_start];
			length++;
			i_start++;
		}
		else
		{
			temp_arr[length] = arr[j_start];
			length++;
			j_start++;
		}
	}
	
	while(i_start <= i_end)
	{
		temp_arr[length] = arr[i_start];
		length++;
		i_start++;
	}
	
	while(j_start <= j_end)
	{
		temp_arr[length] = arr[j_start];
		length++;
		j_start++;
	}
	
	//辅助空间数据覆盖原空间
	for (i = 0; i < length;i++){
		arr[arr_begin + i] = temp_arr[i];
	}
	return 0;
}

//归并
int Merge_sort(int *arr,int arr_begin,int arr_length,int *temp_arr)
{
	if(arr_begin >= arr_length)
	{
		//递归结束条件
		return 0;
	}
	
	int mid = (arr_begin + arr_length) / 2;
	Merge_sort(arr,arr_begin,mid,temp_arr);
	Merge_sort(arr,mid + 1,arr_length,temp_arr);
	
	Merge(arr,arr_begin,arr_length,mid,temp_arr);
	return 0;
}

//调整堆
int Heap_adjust(int* arr,int index,int arr_length)
{
	//保存当前节点下标
	int max = index;
	int temp = 0;
	
	int lchild = index * 2 + 1;
	int rchild = index * 2 + 2;
	if(lchild < arr_length && arr[lchild] > arr[max])
	{
		max = lchild;
	}
	if(rchild < arr_length && arr[rchild] > arr[max])
	{
		max = rchild;
	}
	if(max != index)
	{
		temp = arr[index];
		arr[index] = arr[max];
		arr[max] = temp;
		
		Heap_adjust(arr,max,arr_length);
	}
	return 0;
}

//堆排序
int Heap_sort(int* arr,int arr_length)
{
	int i = 0;
	int temp = 0;
	
	//初始化堆
	for(i = arr_length/2 -1;i >= 0;i--)
	{
		Heap_adjust(arr,i,arr_length);
	}
	
	//交换堆顶和最后一个元素
	for(i = arr_length - 1;i >= 0;i--)
	{
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		
		Heap_adjust(arr,0,i);
	}
	return 0;
}



