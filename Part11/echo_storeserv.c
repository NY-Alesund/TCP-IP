/*************************************************************************
	> File Name: mpserv.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月11日 星期五 13时50分39秒
 ************************************************************************/

/* 实现并发服务器端*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 100
void error_handling(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}

/* Handler */
void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid = waitpid(-1,&status,WNOHANG);
	printf("removed proc id: %d \n",pid);
}

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int fds[2];

	pid_t pid;
	struct sigaction act;
	socklen_t adr_sz;
	int str_len, state;
	char buf[BUF_SIZE];
	if (argc != 2) {
		printf("Usage: %s <port> \n",argv[0]);
		exit(1);
	}

	act.sa_handler = read_childproc;			//设置信号处理函数
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	state = sigaction(SIGCHLD,&act,0);			//子进程终止时调用Handler
	
	serv_sock = socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock,5) == -1)
		error_handling("listen() error");

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		FILE* fp = fopen("echomsg.txt","wt");
		char msgbuf[BUF_SIZE];
		int i, len;

		for (i = 0; i < 10; i++ )
		{
			len = read(fds[0],msgbuf,BUF_SIZE);	//从管道出口fds[0]读取数据并保存到文件中
			fwrite((void*)msgbuf,1,len,fp);		
		}
		fclose(fp);
		return 0;				//调用信号处理函数read_childproc
	}


	while (1) 
	{
		adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);
		if (clnt_sock == -1)
			continue;
		else 
			puts("new client connected...");
		
		pid = fork();
		if (pid == 0)		//子进程运行区域
		{
			close(serv_sock);
			while((str_len = read(clnt_sock,buf,BUF_SIZE)) != 0)
			{	
				write(clnt_sock,buf,str_len);
				write(fds[1],buf,str_len);		//将从客户端接收到的数据写入到管道入口fds[1]中
			}

			close(clnt_sock);
			puts("client disconnected...");
			return 0;		//调用Handler
		}
		else				//父进程运行区域
			close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}
