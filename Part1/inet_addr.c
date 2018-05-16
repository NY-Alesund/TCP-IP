/*************************************************************************
	> File Name: inet_addr.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2018年04月30日 星期一 15时17分25秒
 ************************************************************************/
/* inet_addr函数将点分十进制转换为32为整型数据。并且该整型值满足网络字节序 */
#include<stdio.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
	char *addr1 = "1.2.3.4";
	char *addr2 = "1.2.3.256";			//256是错误的IP地址，检测该函数的错误检测能力

	unsigned long conv_addr = inet_addr(addr1);
	if (conv_addr == INADDR_NONE)
		printf("Error! \n");
	else 
		printf("Network ordered integer addr: %#lx \n",conv_addr);
	
	conv_addr = inet_addr(addr2);
	if(conv_addr == INADDR_NONE)
		printf("Error! \n");
	else 
		printf("Network ordered integer addr: %#lx \n",conv_addr);

	return 0;
}
