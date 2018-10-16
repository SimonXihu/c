#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct VECTOR
{
	int* paddr;
	int size;
	int capacity;
}vector;

//init
vector* init_vector(void);

//insert
int insert_param_to_vector(vector* vec,int pos,int data);

//delete
int delete_param_to_vector(vector* vec,int pos);

//free
int free_vector(vector* vec);

//get
int get_param_vector(vector* vec,int pos);

//clear
int clear_vector(vector* vec);

//print
void print_vector(vector* vec);
#endif