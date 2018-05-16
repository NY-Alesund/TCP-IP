/*************************************************************************
	> File Name: sigaction.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月11日 星期五 11时27分42秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)
{
	if (sig == SIGALRM)
		puts("Time out!");
	alarm(2);
}

int main(int argc, char *argv[])
{
	int i;
	struct sigaction act;		//声明sigaction结构体变量
	act.sa_handler = timeout;	//在sa_handler中保存处理函数指针值
	sigemptyset(&act.sa_mask);	//将sa_mask所有位初始化为0
	act.sa_flags = 0;			//sa_flags成员初始化为0
	sigaction(SIGALRM,&act,0);

	alarm(2);

	for (i = 0; i < 5; i++)
	{
		puts("wait ...");
		sleep(100);
	}
	return 0;
}
