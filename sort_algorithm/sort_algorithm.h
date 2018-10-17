#define ARRLENGTH 20
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