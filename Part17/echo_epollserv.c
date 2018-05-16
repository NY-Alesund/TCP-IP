/*************************************************************************
	> File Name: echo_selectserv.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月12日 星期六 17时53分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/epoll.h>

#define BUF_SIZE 100
#define EPOLL_SIZE 50
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t adr_sz;
	int str_len, i;
	char buf[BUF_SIZE];
	
	struct epoll_event *ep_events;
	struct epoll_event event;
	int epfd, event_cnt;

	if (argc != 2)
	{
		printf("Usage: %s <port> \n",argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error!");
	if (listen(serv_sock,5) == -1)
		error_handling("listen() error!");

	epfd = epoll_create(EPOLL_SIZE);		//创建epoll例程文件描述符
	ep_events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

	event.events = EPOLLIN;
	event.data.fd = serv_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);	//在epfd内注册监视serv__sock,监视其读取数据的情况

	while(1)
	{
		event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);	//成功返回发生事件的文件描述符数。失败返回-1.发生事件的文件描述符保存到events所指的结构体中
		if (event_cnt == -1)
		{
			puts("epoll_wait() error!");
			break;
		}

		for (i = 0; i < event_cnt; i++)		
		{
			if (ep_events[i].data.fd == serv_sock)	//服务器端套接字接收连接
			{
				adr_sz = sizeof(clnt_adr);
				clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);
				event.events = EPOLLIN;
				event.data.fd = clnt_sock;
				epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sock,&event);	//注册监视连接客户端套接字clnt_sock,监视其读取数据的情况 
				printf("connected client: %d \n",clnt_sock);
			}
			else			//连接客户端套接字读取数据
			{
				str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
				if (str_len == 0)		//close request
				{
					epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);
					close(ep_events[i].data.fd);
					printf("closed client: %d \n",ep_events[i].data.fd);
				}
				else 
				{
					write(ep_events[i].data.fd, buf, str_len);		//echo!
				}
			}
		}
	}
	close(serv_sock);
	close(epfd);
	return 0;

}



void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
