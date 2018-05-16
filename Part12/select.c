/*************************************************************************
	> File Name: select.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月12日 星期六 17时06分06秒
 ************************************************************************/

/* select函数调用示例 */
#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	fd_set reads, temps;
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;
	
	FD_ZERO(&reads);
	FD_SET(0,&reads);			//在reads中将文件描述符0对应的位设置为1,表示需要监视标准输入的变化

	/*
	 * timeout.tv_sec  = 5;
	 * timeout.tv_usec = 5000;
	*/

	while(1)
	{
		temps = reads;			//将reads的内容复制到temps中，因为调用select函数后,除发生变化的文件描述符对应位外,剩下的所有位将初始化为0.因此为了记住初始值,必须经过这种复制过程。
		timeout.tv_sec  = 5;
		timeout.tv_usec = 0;	//每次调用select函数前都要初始化timeval结构体变量
		result = select(1,&temps,0,0,&timeout);	//如果控制台输入数据,则返回大于0的整数
		if (result == -1)
		{
			puts("select() error!");
			break;
		}
		else if(result == 0)
		{
			puts("Time-out!");		//超时
		}
		else						//文件描述符发生了变化
		{
			if(FD_ISSET(0,&temps))
			{
				str_len = read(0,buf,BUF_SIZE);	
				buf[str_len] = 0;
				printf("message from console: %s",buf);
			}
		}
	}
	return 0;
}
