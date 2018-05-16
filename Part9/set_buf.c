/*************************************************************************
	> File Name: set_buf.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月09日 星期三 22时19分23秒
 ************************************************************************/

/* setsockopt()设置套接字一些特性
 * 本例设置I/O缓冲大小
 * */

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

int main(int argc,char *argv[])
{
	int sock;
	int snd_buf = 3072 ,	rcv_buf = 3072;
	int state;
	socklen_t len;

	sock = socket(PF_INET,SOCK_STREAM,0);
	
	state = setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,sizeof(rcv_buf));
							//设置输入缓冲长度为rcv_buf
	if (state)
		error_handling("setsockopt() error!");


	state = setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,sizeof(snd_buf));
							//设置输出缓冲长度为snd_buf
	if (state)
		error_handling("setsockopt() error!");

	len = sizeof(snd_buf);
	state = getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,&snd_buf);
	if (state)
		error_handling("getsockopt() error!");

	len = sizeof(rcv_buf);
	state = getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,&rcv_buf);
	if (state)
		error_handling("getsockopt() error!");

	printf("Input  buffer size : %d \n",rcv_buf);
	printf("Output buffer size : %d \n",snd_buf);
	return 0;
}
