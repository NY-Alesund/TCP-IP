/*************************************************************************
	> File Name: waitpid.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月10日 星期四 23时39分21秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		sleep(15);		//推迟子进程的执行，这会导致程序延迟15秒
		return 24;
	}
	else 
	{
		while (!waitpid(-1,&status,WNOHANG))	//传递WHNOHANG参数，若没有终止的子进程将返回0
		{
			sleep(3);
			puts("sleep 3sec.");
		}

		if (WIFEXITED(status))		
			printf("Child send %d \n",WEXITSTATUS(status));	//WEXITSTATUS返回子进程的返回值	
	}
	return 0;
}
