/*************************************************************************
	> File Name: hello_server.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年04月30日 星期一 18时51分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int main(int argc,char *argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[] = "Hello,world!";

	if(argc != 2)
	{
		printf("Usage : %s <port> \n",argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET,SOCK_STREAM,0);				//调用socket函数创建套接字，serv_sock套接字文件描述符
	
	printf("serv_sock: %d \n",serv_sock);

	if (serv_sock == -1)
		error_handling("socket() error ");

	memset(&serv_addr,0,sizeof(serv_addr));					//初始化，使所有字节为0
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);			//自动获取服务器端IP地址
	serv_addr.sin_port = htons(atoi(argv[1]));				//根据命令行参数初始化端口号
	
	//分配地址信息给套接字
	if (bind(serv_sock,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	if(listen(serv_sock,5) == -1)							//调用listen函数将套接字转为可接受连接状态
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock,(struct sockaddr*) &clnt_addr,&clnt_addr_size);	//调用accept函数受理连接请求
	/* 如果accept成功,返回值是由内核生成的一个全新描述符,代表与客户端的TCP连接 */
	
	printf("clnt_sock: %d\n",clnt_sock);
	if (clnt_sock == -1)
		error_handling("accept() error");

	write(clnt_sock,message,sizeof(message));				//使用write函数传输数据
	close(clnt_sock);
	close(serv_sock);

	return 0;
}
