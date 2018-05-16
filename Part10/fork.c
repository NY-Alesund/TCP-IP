/*************************************************************************
	> File Name: fork.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月10日 星期四 14时09分53秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

int gval = 10;
int main(int argc,char *argv[])
{
	pid_t pid;
	int lval = 20;
	gval++, lval+=5;

	pid = fork();
	if (pid == 0)				//子进程
		gval += 2, lval += 2;
	else						//父进程
		gval -= 2, lval -= 2;
	
	if (pid == 0)				//子进程
		printf("Chile  Proc: [%d,%d] \n",gval,lval);
	else						//父进程
		printf("Parent Proc: [%d,%d] \n",gval,lval);
	return 0;
}
