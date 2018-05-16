/*************************************************************************
	> File Name: echo_client.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月02日 星期三 23时46分26秒
 ************************************************************************/

/* 计算客户端 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int main(int argc,char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int len,str_len;
	struct sockaddr_in serv_adr;

	if(argc != 3) {
		printf("Usage : %s <IP> <port>\n",argv[0]);
		exit(1);
	}
	
	sock = socket(PF_INET,SOCK_STREAM,0);
	if (sock == -1)
		error_handling("socket() error!");

	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if (connect(sock,(struct sockaddr*) &serv_adr,sizeof(serv_adr)) == -1)
		error_handling("connect() error!");
	else 
		puts("Connected.........");
	
	scanf("%d",&len);
	for (int i=0; i < len; i++ ) {
		printf("读入第%d个数据:",i+1);
		scanf("%d",(int*)&message[i];
	}
	
	fgetc(stdin);				//读取运算符之前先用fgetc函数删除缓冲区中的字符\n
	printf("读取operator:");
	scanf("%c",&message[len]);

	write(sock,message,strlen(message));
	int result = 0;
	read(sock,&result,len);
	printf("The result is %d",result);
	
	close(sock);
	return 0;
}
