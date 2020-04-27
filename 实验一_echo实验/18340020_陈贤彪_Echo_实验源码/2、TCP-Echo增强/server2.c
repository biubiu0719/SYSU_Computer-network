/* server2.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define BUFLEN          2000 

void toStringIP(const unsigned int ip,char *stringIP)
{
   unsigned int tempIP=ip;
   for(int i=0;i<3;i++)
   {
      unsigned char part=(char)tempIP;
      char temp[4];
      sprintf(temp,"%d.",part);
      strcat(stringIP,temp);
      tempIP=tempIP>>8;
   }
   unsigned char part=(char)tempIP;
   char temp[4];
   sprintf(temp,"%d",part);
   strcat(stringIP,temp);
}
int main(int argc, char *argv[])
/* argc: 命令行参数个数， 例如：C:\> TCPServer 8080
                     argc=2 argv[0]="TCPServer",argv[1]="8080" */
{
     //fsin 客户端地址
        struct  sockaddr_in fsin;           	/* the from address of a client       */
        int     msock, ssock;               	/* master & slave sockets         */
        char    *service = "50500";
        struct  sockaddr_in sin;        	/* an Internet endpoint address             */
        //服务器地址 sin
        int     alen;                       	/* from-address length                      */
        char    *pts;                       	/* pointer to time string           */
        time_t  now;                        	/* current time                                 */
        char    rec[BUFLEN+1];
        char   sen[BUFLEN+1];
        msock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);  	// 创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
                                                           	// 返回：要监听套接字的描述符或INVALID_SOCKET

        memset(&sin,'\0', sizeof(sin));                     	// 从&sin开始的长度为sizeof(sin)的内存清0
        sin.sin_family = AF_INET;                                                       // 因特网地址簇(INET-Internet)
        sin.sin_addr.s_addr = INADDR_ANY;                     	// 监听所有(接口的)IP地址。
        sin.sin_port = htons((u_short)atoi(service));         	// 监听的端口号。atoi--把ascii转化为int，htons--主机序到网络序(host to network，s-short 16位)
        bind(msock, (struct sockaddr *)&sin, sizeof(sin));  	// 绑定监听的IP地址和端口号

        listen(msock, 5);                                   	// 建立长度为5的连接请求队列，并把到来的连接请求加入队列等待处理。
        while(1){                                           	// 检测是否有按键,如果没有则进入循环体执行
           alen = sizeof(struct sockaddr);                	// 取到地址结构的长度
          printf("\n正在接受请求");
           ssock = accept(msock, (struct sockaddr *)&fsin, &alen); 
           char *stringIP= (char*)malloc(16);
           memset(stringIP,0,16+1);
           toStringIP(fsin.sin_addr.s_addr,stringIP);
           ushort duan=fsin.sin_port;
           
           int aa= recv(ssock,rec, BUFLEN, 0);  
         rec[aa] = '\0';
         //printf("收到消息:");
          printf("\n收到消息:  %s",rec);
           (void)time(&now);                                      	// 取得系统时间
           pts =(char *)ctime(&now);                          	// 把时间转换为字符串
           int len = strlen(pts);
           sprintf(sen," \t内容%s\n \t时间:%s \t客户端IP地址:%s \n \t客户端端口号:%d",rec,pts,stringIP,duan);
              int cc = send(ssock, sen, strlen(sen), 0);   

          printf("\n收到时间:%s", pts);                                  	// 显示发送的字符串
         printf("客户端IP地址:%s",stringIP);
         printf("\n客户端端口号:%d",duan);

        
          close(ssock);                              		// 关闭连接套接字
     }
     close(msock);                                 		// 关闭监听套接字
}