#include <stdio.h>

int main(void)
{
	int b[10];
	printf("b=%d\n",b);	
	printf("b+1=%d\n",b+1);	
	printf("&b+1=%d\n",&b+1);	
	int a[10][10];
	printf("a=%d\n",a);	
	printf("a+1=%d\n",a+1);	
	printf("&a+1=%d\n",&a+1);	
	return 0;
}
