/*************************************************************************
	> File Name: zombie.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月10日 星期四 15时38分27秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	pid_t pid = fork();

	if (pid == 0)		//if Child Process
	{
		puts("Hi,I am a child process!");
	}
	else 
	{
		printf("Child Process ID: %d \n",pid);	//父进程保存子进程pid
		sleep(30);		//父进程暂停30秒。	
	}

	if (pid == 0)
		puts("End child process!");
	else 
		puts("End parent process!");
	return 0;
}
