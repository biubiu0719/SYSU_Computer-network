#include<stdio.h>
 #include<sys/types.h>
 #include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
 #include<netinet/in.h>
#include<string.h>
 int main()
{
    const int PORT = 50500;
    const char* IP = "127.0.0.1";
    //const char* IP = "192.168.0.145";
    const int LEN = 100;
    int clientSock;
    //SOCKET	sock;
    struct sockaddr_in server;
    //struct sockaddr_in client; 
     clientSock = socket(AF_INET, SOCK_DGRAM, 0);
//int   fromsize = sizeof(client);
     server.sin_family = AF_INET;
     server.sin_addr.s_addr = inet_addr(IP);
     server.sin_port = htons(PORT);
    int sin_len=sizeof(server);
     char buf[LEN];
     //bind(clientSock,(struct sockaddr *)&server,sizeof(server));
     while(1)
     {
         memset(buf, '\0', LEN);
         printf("please input: ");
         scanf("%s",buf);
        //printf("输入完成");
         int ret = sendto(clientSock, buf, strlen(buf), 0, (struct sockaddr*)&server, sizeof(server));
         printf("sent完成:%d",ret);
         if(ret == SOCKET_ERROR)
         {
             printf("[-] 发送失败\n");
             return 0;
         }
        if(strcmp(buf, "quit") == 0)
         {
            close(clientSock);
             return 0;
         }
         int  rea = recvfrom(clientSock, buf, LEN - 1, 0, (struct sockaddr*)&server,  sizeof(server));
         printf("\n%s\n",buf);
    }

    return 0;
 }