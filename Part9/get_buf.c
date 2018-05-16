/*************************************************************************
	> File Name: get_buf.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月09日 星期三 21时00分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/tcp.h>

void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

int main(int argc,char *argv[])
{
	int sock;
	int snd_buf,rcv_buf,state;
	int opt_val;
	socklen_t len, opt_len;

	sock  = socket(PF_INET,SOCK_STREAM,0);
	
	len	  = sizeof(snd_buf);
	state =	getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,&len);		//SO_SNDBUF代表读取输出(发送)缓冲区
	if (state)
		error_handling("getsockopt() error!");

	len	  = sizeof(rcv_buf);
	state = getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,&len);		//SO_RCVBUF代表读取输入(接收)缓冲区
	if (state)
		error_handling("getsockopt() error!");

	printf("Input  buffer size: %d \n",rcv_buf);
	printf("Output buffer size: %d \n",snd_buf);
	
	
	opt_len = sizeof(opt_val);
	getsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void*)&opt_val,&opt_len);
	printf("Nagle bit is : %d \n",opt_val);	

	return 0;
}
