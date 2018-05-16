/*************************************************************************
	> File Name: todes.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月13日 星期日 20时27分29秒
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>

int main(void)
{
	FILE *fp;
	int fd = open("data.dat", O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		fputs("file open error",stdout);
		return -1;
	}

	printf("First file description: %d \n",fd);			//输出文件描述符整数值
	fp = fdopen(fd,"w");						//转化为FILE指针
	fputs("TCP/IP SOCKET PROGRAMMING \n",fp);
	printf("Second file description: %d \n",fileno(fp));//转化为文件描述符,并输出
	fclose(fp);
	return 0;
}
