/*************************************************************************
	> File Name: gethostbyname.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月06日 星期日 23时42分25秒
 ************************************************************************/

/* gethostbyname函数的应用:并说明hostent结构体变量的特性 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int main(int argc,char *argv[])
{
	int i;
	struct hostent *host;
	if (argc != 2)
	{
		printf("Usage: %s <addr> \n",argv[0]);
		exit(1);
	}

	host = gethostbyname(argv[1]);
	if (!host)
		error_handling("gethostbyname() error!");

	printf("Official name：%s \n",host->h_name);			//输出官方域名
	
	for (i = 0; host->h_aliases[i]; i++)					//输出除官方域名外的其它域名
		printf("Aliases %d: %s \n",i+1,host->h_aliases[i]);
	
	printf("Address type: %s \n",(host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

	for (i = 0; host->h_addr_list[i]; i++)					//输出IP地址信息
		printf("IP addr %d: %s \n",i+1,inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
	
	return 0;
}

