/*************************************************************************
	> File Name: pipe2.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月11日 星期五 21时34分12秒
 ************************************************************************/

/* 双向通信的管道 */
#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc,char *argv[])
{
	int fds[2];
	char str1[] = "Who are you?";
	char str2[] = "Thank you for your message!";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		write(fds[1],str1,sizeof(str1));		//传输数据
		sleep(2);
		read(fds[0],buf,BUF_SIZE);
		printf("Child proc output: %s \n",buf);	//接收数据
	}
	else 
	{
		read(fds[0],buf,BUF_SIZE);				//接收数据
		printf("Parent proc output: %s \n",buf);
		write(fds[1],str2,sizeof(str2));		//传输数据
		sleep(3);		//睡眠,防止父进程在子进程输出之前结束
	}
	return 0;
}
