/*************************************************************************
	> File Name: remove_zombie.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月11日 星期五 12时01分25秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

void read_childproc(int sig)
{
	int status;
	pid_t id = waitpid(-1,&status,WNOHANG);	//调用waitpid函数，若子进程正常终止，不会成为僵尸进程
	if (WIFEXITED(status))
	{
		printf("Removed proc id: %d \n",id);
		printf("Child send: %d \n",WEXITSTATUS(status));
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;
	struct sigaction act;
	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD,&act,0);			//注册子进程终止(SIHCHLD)的信号,若子进程终止，调用read_childproc函数。

	pid = fork();
	if (pid == 0)		//子进程执行区域
	{
		puts("Hi! I'm child process one~");
		sleep(10);
		return 12;		//子进程终止，发出SIHCHLD信号，sigaction函数调用read_childproc处理函数
	}
	else				//父进程执行区域
	{	
		sleep(1);		//睡眠1s是为了延迟下一句printf的输出时间，让子进程先输出。下同
		printf("Child proc id: %d \n",pid);
		pid = fork();
		if (pid == 0)	//另一子进程执行区域
		{
			puts("Hi! I'm child process two~");
			sleep(10);
			exit(24);	//子进程终止，发出SIHCHLD信号， sigaction函数调用read_childproc处理函数
		}
		else 
		{
			sleep(1);
			int i;
			printf("Child proc id: %d \n",pid);
			for (i = 0; i < 5; i++)
			{
				puts("wait ...");
				sleep(5);
			}
		}
	}
	return 0;

}
