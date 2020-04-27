#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>
#include <string.h>
const int PORT = 50500;
const int LEN = 100;
int serverSock;
struct sockaddr_in local;
struct sockaddr_in client;
 int main()
{
serverSock = socket(AF_INET, SOCK_DGRAM, 0);

     local.sin_family = AF_INET;
     //local.sin_addr.s_addr = htonl(INADDR_ANY);
     local.sin_port = htons(PORT);
     local.sin_addr.s_addr = inet_addr("127.0.0.1");
     bind(serverSock, (struct sockaddr*)&local, sizeof(local));

    char buf[LEN];
     while(1)
    {
         int ret = 0;
         socklen_t  len = sizeof(client);
        memset(buf, '\0', LEN);
         ret = recvfrom(serverSock, buf, LEN - 1, 0, (struct sockaddr*)&client, &len);
         //printf("ret is %d", ret);
        if(ret == 0)
         {
             printf("client is closed!\n");
             exit(2);
         }
         else if(ret < 0)
         {
             perror("recvfrom");
             continue;
         }
         else
         {
             time_t  now; 
             char    *pts;
             (void)time(&now); 
            pts =(char *)ctime(&now);
             buf[ret] = '\0';
             printf("\n客户端消息: %s \n客户端IP地址: %s \n客户端端口号:%d \n时间:%s",buf,inet_ntoa(client.sin_addr),ntohs(client.sin_port),pts);
             //printf("client[ip:%s][port:%d]# %s\n", inet_ntoa(client.sin_addr), \
                     ntohs(client.sin_port), buf);
    char sen[LEN];
    sprintf(sen,"\n客户端消息: %s \n客户端IP地址: %s \n客户端端口号:%d \n时间:%s",buf,inet_ntoa(client.sin_addr),ntohs(client.sin_port),pts);
            //发送
            int rea = sendto(serverSock, sen, strlen(sen), 0, (struct sockaddr*)&client, sizeof(client));

             fflush(stdout);
         }
 
         if(strstr(buf, "quit") != NULL)
         {
             close(serverSock);
            return 0;
         }
     }
     return 0;
 }