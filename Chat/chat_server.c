/*************************************************************************
	> File Name: echo_server.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月03日 星期四 19时34分53秒
 ************************************************************************/

/* 聊天服务器端chat_server.c */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>
#define BUF_SIZE 100
#define MAX_CLNT 256

void error_handling(char *message);
void * handle_clnt(void * arg);
void send_msg(char * msg,int len);

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];	//管理接入的客户端套接字的数组
pthread_mutex_t mutx;

int main(int argc,char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	pthread_t t_id;

	if (argc != 2) {
		printf("Usage : %s <port> \n",argv[0]);
		exit(1);
	}

	pthread_mutex_init(&mutx,NULL);
	serv_sock = socket(PF_INET,SOCK_STREAM,0);
	if (serv_sock == -1)
		error_handling("socket() error!");

	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock,(struct sockaddr*) &serv_adr,sizeof(serv_adr)) == -1)
		error_handling("bind() error!");

	if (listen(serv_sock,5) == -1)
		error_handling("listen() error!");

	while(1)
	{
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);

		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++] = clnt_sock;		//每当有新连接，将连接的套接字写入变量clnt_cnt和clnt_socks
		pthread_mutex_unlock(&mutx);

		pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);	//创建线程向接入的客户端提供服务
		pthread_detach(t_id);		//从内存中完全销毁已终止的线程
		printf("Connected client IP: %s \n",inet_ntoa(clnt_adr.sin_addr));
	}
	close(serv_sock);
	return 0;
}

void * handle_clnt(void * arg)
{
	int clnt_sock = *((int*)arg);
	int str_len = 0, i;
	char msg[BUF_SIZE];

	while((str_len = read(clnt_sock,msg,sizeof(msg))) != 0)		//从一个客户端读取消息
		send_msg(msg,str_len);

	pthread_mutex_lock(&mutx);
	for (i=0; i<clnt_cnt; i++)		//remove disconnected client 
	{
		if (clnt_sock == clnt_socks[i])
		{
			while(i++ < clnt_cnt-1)
				clnt_socks[i] = clnt_socks[i+1];
			break;
		}
	}

	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
	return NULL;
}

void send_msg(char * msg,int len)	//send to all：向所有客户端发送消息
{
	int i;
	pthread_mutex_lock(&mutx);
	for ( i=0; i<clnt_cnt; i++)
		write(clnt_socks[i], msg, len);
	pthread_mutex_unlock(&mutx);
}

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
