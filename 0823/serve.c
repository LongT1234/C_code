#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    //创建套接字
    int sockfd1 = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd1 == -1)
    {
        perror("socket");
        return -1;
    }
    perror("socket");
    //绑定ip和端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = bind(sockfd1,(struct sockaddr *)&addr,sizeof(addr));
    if(res == -1)
    {
        perror("bind");
        return -1;
    }
    perror("bind");
    //设置最大监听数量
    res = listen(sockfd1,3);
    if(res == -1)
    {
        perror("listen");
        return -1;
    }
    perror("listen");
    //等待客户端连接，并且生成通信使用的套接字
    struct sockaddr_in o_addr;
    socklen_t len = sizeof(o_addr);
    int cfd = accept(sockfd1,(struct sockaddr *)&o_addr,&len);
    if(cfd == -1)
    {
        perror("accept");
        return -1; 
    }
    perror("accept");
    printf("%d号客户端已连接\n",cfd);
    char w_buf[100] = {0};
    char r_buf[100] = {0};
    int a = 0;
    while(1)
    {
        a = recv(cfd,r_buf,sizeof(r_buf),0);
        if(a == 0)
        {
            printf("%d号客户端下线\n",cfd);
            break;
        }
        printf("从客户端接收到：%s\n",r_buf);
        printf("请输入要想客户端发送的内容：\n");
        scanf("%s",w_buf);
        getchar();
        send(cfd,w_buf,sizeof(w_buf),0);
        memset(w_buf,0,100);
    }
    return 0 ;
}