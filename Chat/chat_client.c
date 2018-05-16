/*************************************************************************
	> File Name: echo_client.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月02日 星期三 23时46分26秒
 ************************************************************************/

/* 聊天程序客户端 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>
#define BUF_SIZE 1024
#define NAME_SIZE 20

void * send_msg(void * arg);
void * recv_msg(void * arg);
void error_handling(char *message);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

int main(int argc,char *argv[])
{
	int sock;
	struct sockaddr_in serv_adr;
	pthread_t snd_thread, rcv_thread;
	void * thread_return;

	if(argc != 4) {
		printf("Usage : %s <IP> <port> <name> \n",argv[0]);
		exit(1);
	}
	
	sprintf(name,"[%s]", argv[3]);			//第四个参数为客户端名字
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

	pthread_create(&snd_thread,NULL,send_msg,(void*)&sock);
	pthread_create(&rcv_thread,NULL,recv_msg,(void*)&sock);
	pthread_join(snd_thread,&thread_return);	//返回值保存到thread_return
	pthread_join(rcv_thread,&thread_return);	//返回值保存到thread_return
	close(sock);
	return 0;
}

void * send_msg(void * arg)		//send thread main
{
	int sock = *((int*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	while(1)
	{
		fgets(msg,BUF_SIZE,stdin);	//读取输入到msg
		if (!strcmp(msg,"q\n") || !strcmp(msg,"Q\n"))
		{
			close(sock);
			exit(0);
		}
		sprintf(name_msg,"%s %s",name,msg);	//把名字和消息写入name_msg数组
		write(sock,name_msg,strlen(name_msg));
	}
	return NULL;
}

void * recv_msg(void * arg)		//read thread main 
{
	int sock= *((int*)arg);
	char name_msg[NAME_SIZE+BUF_SIZE];
	int str_len;
	while(1)
	{
		str_len = read(sock,name_msg,NAME_SIZE+BUF_SIZE-1);
		if (str_len == -1)
			return (void*)-1;
		name_msg[str_len] = 0;
		fputs(name_msg,stdout);
	}
	return NULL;
}

void error_handling(char *msg)
{
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}


