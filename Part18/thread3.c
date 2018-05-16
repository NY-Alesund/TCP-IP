/*************************************************************************
	> File Name: thread3.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月14日 星期一 23时46分40秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
void * thread_summation(void * arg);
int sum = 0;

int main(int argc, char *argv[])
{
	pthread_t id_t1, id_t2;
	int range1[] = {1,5};
	int range2[] = {6,10};

	pthread_create(&id_t1,NULL, thread_summation, (void*)range1);
	pthread_create(&id_t2,NULL, thread_summation, (void*)range2);

	pthread_join(id_t1,NULL);
	pthread_join(id_t2,NULL);
	printf("result: %d \n",sum);
}

void * thread_summation(void *arg)	//此处*arg为数组
{
	int start = ((int*)arg)[0];
	int end   = ((int*)arg)[1];

	while(start <= end)
	{
		sum += start;
		start++;
	}
	return NULL;
}
