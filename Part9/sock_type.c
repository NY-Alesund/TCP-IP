/*************************************************************************
	> File Name: sock_type.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月09日 星期三 20时36分37秒
 ************************************************************************/

/* getsockopt函数的调用方法
 * 用协议层SOL_SOCKET,名为SO_TYPE的可选项查看套接字类型(TCP或UDP) */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
	int tcp_sock, udp_sock;
	int sock_type;
	socklen_t optlen;
	int state;

	optlen = sizeof(sock_type);
	tcp_sock = socket(PF_INET,SOCK_STREAM,0);		//生成TCP套接字
	udp_sock = socket(PF_INET,SOCK_DGRAM,0);		//生成UDP套接字
	printf("SOCK_STREAM: %d \n",SOCK_STREAM);
	printf("SOCK_DGRAM : %d \n",SOCK_DGRAM);
	//输出创建套接字时传入的SOCK_STREAM,SOCK_DGRAM.
	
	/* getsockopt()获取套接字信息
	 * TCP套接字将获得SOCK_STREAM常数值1,UDP套接字将获得SOCK_DGRAM常数值2 */
	state = getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
	if (state)
		error_handling("getsockopt() error!");
	printf("Socket type one : %d \n",sock_type);

	state = getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
	if(state)
		error_handling("getsockopt() error!");
	printf("Socket type two : %d \n",sock_type);
	
	return 0;
}
