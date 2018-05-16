/*************************************************************************
	> File Name: pipe1.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月11日 星期五 21时11分51秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds[2];
	char str[] = "Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);				//创建管道,fds数组中保存用于I/O的文件描述符
	pid = fork();			//子进程将同时拥有管道的I/O文件描述符。
	if (pid == 0)
	{
		write(fds[1],str,sizeof(str));		//fds[1]为管道入口
	}
	else 
	{
		read(fds[0],buf,BUF_SIZE);			//fds[0]为管道出口	
		puts(buf);
	}
	return 0;

}
