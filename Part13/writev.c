/*************************************************************************
	> File Name: writev.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月13日 星期日 00时06分45秒
 ************************************************************************/

#include<stdio.h>
#include<sys/uio.h>

int main(int argc,char *argv[])
{
	struct iovec vec[2];
	char buf1[] = "ABCDEFG";
	char buf2[] = "1234567";
	int str_len;

	vec[0].iov_base = buf1;
	vec[0].iov_len = 3;
	vec[1].iov_base = buf2;
	vec[1].iov_len = 4;

	str_len = writev(1,vec,2);	//输出到标准输出
	puts(" ");
	printf("Write bytes: %d \n",str_len);
	return 0;
}
