/*************************************************************************
	> File Name: readv.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月13日 星期日 00时11分06秒
 ************************************************************************/

#include<stdio.h>
#include<sys/uio.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	struct iovec vec[2];
	char buf1[BUF_SIZE] = {0,};
	char buf2[BUF_SIZE] = {0,};
	int str_len;

	vec[0].iov_base = buf1;
	vec[0].iov_len  = 5;			//第一个数据保存在buf1,长度为5
	vec[1].iov_base = buf2;
	vec[1].iov_len  = BUF_SIZE;		//第二个数据保存在buf2,长度为100

	str_len = readv(0,vec,2);
	printf("Read bytes: %d \n",str_len);
	printf("First message: %s \n",buf1);
	printf("Second message: %s \n",buf2);
	return 0;
}
