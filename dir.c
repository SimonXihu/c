#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc,char *argv[])
{
	printf("%s\n",argv[1]);
	DIR *dir = opendir(argv[1]);
	struct dirent *drent = NULL;
	do
	{
		drent = readdir(dir);
		if(drent != NULL)
			printf("%s\n",drent->d_name);
	}while(drent!=NULL);
	return 0;
}
