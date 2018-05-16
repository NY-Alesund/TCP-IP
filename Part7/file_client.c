/*************************************************************************
	> File Name: file_server.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月06日 星期日 21时36分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sd;
	FILE *fp;

	char buf[BUF_SIZE];
	int read_cnt;
	struct sockaddr_in serv_adr;

	if (argc != 3)
	{
		printf("Usage: %s <port> \n",argv[0]);
		exit(1);
	}

	fp = fopen("receive.dat","wb");						//创建新文件保存服务器端传输的文件数据
	sd = socket(PF_INET,SOCK_STREAM,0);

	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	connect(sd,(struct sockaddr*) &serv_adr,sizeof(serv_adr));

	while ((read_cnt = read(sd,buf,BUF_SIZE)) != 0)
		fwrite((void*)buf,1,read_cnt,fp);				//将接收的数据写入到fp指向的文件receive.dat中

	puts("Receive file data");
	write(sd,"Thank you",10);
	fclose(fp);
	close(sd);
	return 0;
}
