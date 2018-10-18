#define ARRLENGTH 20000
#define true  1
#define false 0
//创建随机数组
int create_arr(int **arr);

//销毁随机数组
int detroy_arr(int **arr);

//冒泡
int Bubble_sort(int *arr,int arr_length);

//选择
int Select_sort(int *arr,int arr_length);

//插入
int Insert_sort(int *arr,int arr_length);

//希尔
int Shell_sort(int *arr,int arr_length);

//快速排序
int Quick_sort(int *arr,int arr_begin,int arr_length);

//归并合并算法
int Merge(int *arr,int arr_begin,int arr_length,int mid,int *temp_arr);

//归并
int Merge_sort(int *arr,int arr_begin,int arr_length,int *temp_arr);

//调整堆
int Heap_adjust(int* arr,int index,int arr_length);

//堆排序
int Heap_sort(int* arr,int arr_length);