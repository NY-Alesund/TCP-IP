/*************************************************************************
	> File Name: sep_serv.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年05月13日 星期日 21时30分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024

int main(int argc,char *argv[])
{
	int serv_sock,clnt_sock;
	FILE * readfp;
	FILE * writefp;

	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	char buf[BUF_SIZE] = {0,};
	
	serv_sock = socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_adr,0,sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	bind(serv_sock,(struct sockaddr*)&serv_adr, sizeof(serv_adr));
	listen(serv_sock,5);
	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);

	readfp = fdopen(clnt_sock,"r");			//创建读模式FILE指针
	writefp = fdopen(clnt_sock,"w");		//创建写模式FILE指针

	fputs("FROM SERVER: HI~ client? \n",writefp);
	fputs("I love all of the world \n",writefp);
	fputs("You are awesome! \n",writefp);
	fflush(writefp);		

	fclose(writefp);						//关闭写模式FILE指针,发送EOF
	fgets(buf,sizeof(buf),readfp);			//使用readfp接收数据
	fputs(buf,stdout);
	fclose(readfp);
	return 0;
}
