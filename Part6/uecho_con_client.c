/*************************************************************************
	> File Name: echo_con_client.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月02日 星期三 23时46分26秒
 ************************************************************************/

/* UDP已连接客户端 */
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

int main(int argc,char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	socklen_t adr_sz;

	struct sockaddr_in serv_adr;	//不需要from_adr

	if(argc != 3) {
		printf("Usage : %s <IP> <port>\n",argv[0]);
		exit(1);
	}
	
	sock = socket(PF_INET,SOCK_DGRAM,0);
	if (sock == -1)
		error_handling("socket() error!");

	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));
	
	connect(sock,(struct sockaddr*) &serv_adr,sizeof(serv_adr));

	while (1) {
		fputs("Input message(Q to quit): ",stdout);
		fgets(message,sizeof(message),stdin);

		if (!strcmp(message,"q\n") || !strcmp(message,"Q\n"))		// 输入q/Q退出
			break;
		/* 
		sendto(sock,message,strlen(message),0,(struct sockaddr*) &serv_adr,sizeof(serv_adr));	
		*/
		
		write(sock,message,strlen(message));			//可以使用write传输数据
		
		/*
		adr_sz  = sizeof(from_adr);
		str_len = recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr*) &from_adr, &adr_sz);
		*/

		str_len = read(sock,message,sizeof(message)-1);	//可以使用read读取数据

		message[str_len] = 0;
		printf("Message from server: %s",message);
	}

	close(sock);
	return 0;
}
