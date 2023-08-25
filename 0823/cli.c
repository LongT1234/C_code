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
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    printf("sockfd = %d\n",sockfd);
    perror("socket");
    //申请连接
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(12345);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = connect(sockfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
    if(res == -1)
    {
        perror("connect");
        return -1;
    }
    perror("connect");
    char w_buf[100] = {0};
    char r_buf[100] = {0};
    while(1)
    {
        printf("请输入要向服务器发送的内容：\n");
        scanf("%s",w_buf);
        getchar();
        send(sockfd,w_buf,sizeof(w_buf),0);
        memset(w_buf,0,100);
        recv(sockfd,r_buf,sizeof(r_buf),0);
        printf("从服务器接受到：%s\n",r_buf);
    }
    close(sockfd);
    return 0;
}