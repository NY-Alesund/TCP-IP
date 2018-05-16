/*************************************************************************
	> File Name: wait.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月10日 星期四 23时08分01秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		return 3;			//终止第一个子进程,返回3
	}
	else 
	{
		printf("Child PID: %d \n",pid);
		pid = fork();
		if (pid == 0)
		{
			exit(7);		//终止第二个子进程，返回7
		}
		else 
		{
			printf("Child PID: %d\n",pid);
			wait(&status);	//将之前终止的子进程相关信息保存到status变量，同时子进程完全销毁
			if (WIFEXITED(status))	//若正常终止，则调用WEXITSTATUS宏输出子进程的返回值
				printf("Child send one: %d \n",WEXITSTATUS(status));
		
			wait(&status);	//因为之前创建了2个进程，所以再次调用wait函数和宏
			if (WIFEXITED(status))
				printf("Child send two: %d \n",WEXITSTATUS(status));
			sleep(30);				//休眠30秒
		}
	}
	return 0;
}
