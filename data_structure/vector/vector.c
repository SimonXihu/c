#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

vector* init_vector(void)
{
	vector* vec = (vector*)malloc(sizeof(vector));
	if(vec == NULL)
	{
		return NULL;
	}
	memset(vec,0,sizeof(vector));
	vec->paddr = (int*)malloc(sizeof(int)*20);
	memset(vec->paddr,0,sizeof(sizeof(int)*20));
	if(vec->paddr == NULL)
	{
		return NULL;
	}
	vec->size = 0;
	vec->capacity = 20;
	return vec;
}

int free_vector(vector* vec)
{
	if(vec == NULL)
	{
		return -1;
	}
	if(vec->paddr == NULL)
	{
		return -1;
	}
	free(vec->paddr);
	free(vec);
	return 0;
}

int insert_param_to_vector(vector* vec,int pos,int data)
{
	int count = 0;
	
	if(vec == NULL)
	{
		return -1;
	}
	if(pos < 0 || pos > vec->size)
	{
		pos = vec->size;
	}
	if(vec->size == vec->capacity)
	{
		vec->capacity = vec->capacity*2;
		int* tmp_paddr = (int*)malloc(vec->capacity * sizeof(int));
		memset(tmp_paddr,0,vec->capacity * sizeof(int));
		memcpy(tmp_paddr,vec->paddr,vec->size * sizeof(int));
		free(vec->paddr);
		vec->paddr = tmp_paddr;
	}
	
	vec->paddr[pos] = data;
	vec->size++;
	
	return 0;
}

int get_param_vector(vector* vec,int pos)
{
	if(vec == NULL)
	{
		return -1;
	}
	if(pos < 0 || pos >= vec->size)
	{
		return -1;
	}
	return vec->paddr[pos];
}

int clear_vector(vector* vec)
{
	if(vec == NULL)
	{
		return -1;
	}
	if(vec->paddr == NULL)
	{
		return -1;
	}
	memset(vec->paddr,0,sizeof(vec->size));
	vec->size = 0;
	return 0;
}

void print_vector(vector* vec)
{
	int count = 0;
	if(vec == NULL)
	{
		return;
	}
	if(vec->paddr == NULL)
	{
		return;
	}
	while(count < vec->size)
	{
		printf("%d ",vec->paddr[count]);
		count++;
	}
	printf("\n");
}

int delete_param_to_vector(vector* vec,int pos)
{
	if(vec == NULL)
	{
		return -1;
	}
	if(vec->paddr == NULL)
	{
		return -1;
	}
	if(pos < 0 || pos >= vec->size)
	{
		return -1;
	}
	int count = pos;
	while(pos < vec->size-1)
	{
		vec->paddr[pos] = vec->paddr[pos+1];
		pos++;
	}
	vec->size--;
	return 0;
}