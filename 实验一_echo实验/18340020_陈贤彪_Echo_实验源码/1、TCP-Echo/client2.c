/* client2.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#define BUFLEN          2000                  			// 缓冲区大小

int
main(int argc, char *argv[])
{
         
        char    *host = "127.0.0.1";        				/* server IP to connect         */
        char    *service = "50500";         				/* server port to connect       */
        struct sockaddr_in sin;             				/* an Internet endpoint address */
        char    buf[BUFLEN+1];    
        char    buf2[BUFLEN+1];          				/* buffer for one line of text  */
        int     sock;                       				/* socket descriptor            */
        int     cc;                         				/* recv character count         */
        // }
        while(1)
        {
         sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);    		//创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
                                                         		//返回：要监听套接字的描述符或INVALID_SOCKET
        memset(&sin, 0, sizeof(sin));                      		// 从&sin开始的长度为sizeof(sin)的内存清0
        sin.sin_family = AF_INET;                        		// 因特网地址簇
        sin.sin_addr.s_addr = inet_addr(host);                		// 设置服务器IP地址(32位)
        sin.sin_port = htons((u_short)atoi(service));        
        int ret=connect(sock, (struct sockaddr *)&sin, sizeof(sin)); 
        if(ret==-1)
        {
                printf("[-] 连接到服务器失败!\n");
                close(sock); 
                return 0; 
        }
 char message[BUFLEN+1];
 printf("\n请输入要发送的消息:");
 scanf("%s",message);
int aa = send(sock, message, strlen(message), 0);


 cc = recv(sock, buf, BUFLEN, 0);
 buf[cc] = '\0'; 
 printf("\n收到消息:\n");
 printf("%s",buf); 

close(sock);      
}
        printf("按回车键继续...");
        getchar();                              			// 等待任意按键
}