#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

sem_t produ;
sem_t consu;

int head=0;

void* produce(void* arg)
{
	int *p=(int*)arg;
	while(1)
	{
		sem_wait(&produ);
		head++;
		printf("%d--produce--head=%d\n",*p,head);
		sem_post(&consu);
		sleep(1);
	}
}
void* consume(void* arg)
{
	int *p=(int*)arg;
	while(1)
	{
		sem_wait(&consu);
		head--;
		printf("%d--consume--head=%d\n",*p,head);
		sem_post(&produ);
		sleep(1);
	}
}
int main(void)
{
	int emp[5];
	int i=0;
	void* p=NULL;
	pthread_t thread[5];
	sem_init(&produ,0,2);
	sem_init(&consu,0,0);
	for(i=0;i<2;i++)
	{
		emp[i]=i;
		p = (void *)(emp+i);
		pthread_create(&thread[i],NULL,produce,p);
		pthread_detach(thread[i]);
	}
	for(;i<5;i++)
	{
		emp[i]=i;
		p = (void *)(emp+i);
		pthread_create(&thread[i],NULL,consume,p);
		pthread_detach(thread[i]);
	}
	printf("jiangxihu----sizeof(size_t)=%u\n",sizeof(size_t));
	while(1);
	return 0;
}
