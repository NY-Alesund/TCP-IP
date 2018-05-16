/*************************************************************************
	> File Name: gethostbyname.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月06日 星期日 23时42分25秒
 ************************************************************************/

/* gethostbyaddr函数的应用 */
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
	struct sockaddr_in addr;

	if (argc != 2)
	{
		printf("Usage: %s <addr> \n",argv[0]);
		exit(1);
	}

	memset(&addr,0,sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(argv[1]);

	host = gethostbyaddr((char*)&addr.sin_addr,4,AF_INET);
	if (!host)
		error_handling("gethostbyaddr() error!");

	printf("Official name：%s \n",host->h_name);			//输出官方域名
	
	for (i = 0; host->h_aliases[i]; i++)					
		printf("Aliases %d: %s \n",i+1,host->h_aliases[i]);	//输出除官方域名外的其它域名
	
	printf("Address type: %s \n",(host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

	for (i = 0; host->h_addr_list[i]; i++)					//输出IP地址信息
		printf("IP addr %d: %s \n",i+1,inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
	
	return 0;
}

