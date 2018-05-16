/*************************************************************************
	> File Name: news_sender.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月13日 星期日 12时11分03秒
 ************************************************************************/

/* 基于广播的Sender */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int send_sock;
	struct sockaddr_in broad_adr;
	FILE *fp;
	char buf[BUF_SIZE];
	int so_brd = 1;

	if (argc != 3) {
		printf("Usage: %s <GroupIP> <PORT> \n",argv[0]);
		exit(1);
	}

	send_sock = socket(PF_INET,SOCK_DGRAM,0);
	memset(&broad_adr,0,sizeof(broad_adr));
	broad_adr.sin_family = AF_INET;
	broad_adr.sin_addr.s_addr = inet_addr(argv[1]);		 
	broad_adr.sin_port = htons(atoi(argv[2]));			

	setsockopt(send_sock,SOL_SOCKET,SO_BROADCAST,(void*)&so_brd,sizeof(so_brd));
	if((fp = fopen("news.txt","r")) == NULL)
		error_handling("fopen() error!");
	
	/* 实际传输数据的区域,基于UDP套接字传输数据,*/
	while(!feof(fp))	
	{
		fgets(buf,BUF_SIZE,fp);	//从fp中读取数据,每次读取一行,每次最多读取BUF_SIZE-1个字符,读取的数据保存到buf
		sendto(send_sock,buf,strlen(buf),0,(struct sockaddr*)&broad_adr,sizeof(broad_adr));		//更改UDP套接字可选项，使其能够发送广播数据
		sleep(2);				//给传输数据提供一定的时间间隔
	}
	close(send_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

