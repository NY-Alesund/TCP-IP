/*************************************************************************
	> File Name: low_open.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年04月30日 星期一 00时19分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void error_handling(char* message);

int main(void)
{
	int fd;
	char buf[] = "Let's go!\n";

	fd = open("data.txt",O_CREAT | O_WRONLY | O_TRUNC);		//必要时创建/只写打开/删除全部现有数据
	if (fd == -1)
		error_handling("open() error!");
	printf("file descriptor: %d \n",fd);

	if(write(fd,buf,sizeof(buf)) == -1)
		error_handling("write() error!");

	close(fd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
