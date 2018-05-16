/*************************************************************************
	> File Name: syscpy.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月13日 星期日 19时59分35秒
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#define BUF_SIZE 3		//用最短数组长度构成

int main(int argc,char *argv[])
{
	int fd1,fd2;		//保存在fd1和fd2中的是文件描述符！
	int len;
	char buf[BUF_SIZE];

	fd1 = open("news.txt",O_RDONLY);
	fd2 = open("cpy.txt",O_WRONLY | O_CREAT | O_TRUNC);

	while ((len = read(fd1,buf,sizeof(buf))) > 0)
		write(fd2,buf,len);

	close(fd1);
	close(fd2);
	return 0;
}
