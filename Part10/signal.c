/*************************************************************************
	> File Name: signal.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月11日 星期五 09时48分36秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)
{
	if (sig == SIGALRM)
		puts("Time out!");
	alarm(2);				//在信号处理器(Handler)中使用alarm函数，会每个2秒重复产生SIGALRM信号 
}

void keycontrol(int sig)
{
	if (sig == SIGINT)
		puts("CTRL+C pressed!");
}

int main(int argc, char *agrv[])
{
	int i;
	signal(SIGALRM,timeout);	//alarm产生SIGALRM信号，进入timeout函数
	signal(SIGINT,keycontrol);	//输入CTRL+Cc产生SIGINT信号，进入keycontrol函数
	alarm(2);

	for (i = 0; i < 5; i++)		//5次等待睡眠，产生信号唤醒进程，睡眠状态被打断。
	{
		puts("wait ...");
		sleep(100);
	}

	return 0;
}
