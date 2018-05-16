/*************************************************************************
	> File Name: semaphore.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月15日 星期二 11时04分44秒
 ************************************************************************/

/* 控制访问顺序的线程同步 */
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

void * read(void * arg);
void * accu(void * arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char *argv[])
{
	pthread_t id_t1,id_t2;
	sem_init(&sem_one,0,0);		//sem_one初始值为0
	sem_init(&sem_two,0,1);		//sem_two初始值为1

	pthread_create(&id_t1,NULL,read,NULL);
	pthread_create(&id_t2,NULL,accu,NULL);

	pthread_join(id_t1,NULL);
	pthread_join(id_t2,NULL);

	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}

void * read(void * arg)
{
	int i;
	for(i=0; i<5; i++)
	{
		fputs("Input num: ",stdout);

		sem_wait(&sem_two);		//sem_two变为0,阻塞,在accu中加1后跳出阻塞状态
		scanf("%d",&num);
		sem_post(&sem_one);		//sem_one变为1
	}
	return NULL;
}

void * accu(void * arg)
{
	int sum=0, i;
	for(i=0; i<5; i++)
	{
		sem_wait(&sem_one);		//sem_one变为0,阻塞,在read中加1后跳出阻塞状态
		sum+=num;
		sem_post(&sem_two);		//sem_two变为1
	}
	printf("Result: %d \n",sum);
	return NULL;
}


