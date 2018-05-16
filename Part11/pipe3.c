/*************************************************************************
	> File Name: pipe3.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月11日 星期五 22时00分50秒
 ************************************************************************/

/* 双管道实现进程间通信 */
#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc,char *argv[])
{
	int fds1[2],fds2[2];
	char str1[] = "Who are you?";
	char str2[] = "Thank you for your message!";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds1), pipe(fds2);						//创建两个管道
	pid = fork();
	if (pid == 0)
	{
		write(fds1[1],str1,sizeof(str1));	//子进程通过数组fds1传输数据
		read(fds2[0],buf,BUF_SIZE);
		printf("Child proc output: %s \n",buf);
	}
	else 
	{
		read(fds1[0],buf,BUF_SIZE);
		printf("Parent proc output: %s \n",buf);	
		write(fds2[1],str2,sizeof(str2));	//父进程通过数组fds2传输数据
		sleep(3);
	}
	return 0;
}
