/*************************************************************************
	> File Name: thread1.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月14日 星期一 22时59分19秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void* thread_main(void *arg);

int main(int argc, char *argv[])
{
	pthread_t t_id;
	int thread_param = 5;

	/* 创建一个线程,从thread_main函数调用开始,在单独执行流运行。同时向其传递thread_param变量的地址值 */
	if (pthread_create(&t_id,NULL,thread_main,(void*)&thread_param) != 0)
	{
		puts("pthread_create() error");
		return -1;
	};
	sleep(10);				//延迟进程的终止时间。保证线程的正常执行。 
	puts("end of main");
	return 0;
}

void* thread_main(void *arg)	//传入arg参数的是第四个参数thread_param
{
	int i;
	int cnt = *((int*)arg);		//arg值为5
	for (i=0; i<cnt; i++)
	{
		sleep(1);	puts("running thread");
	}
	return NULL;
}


