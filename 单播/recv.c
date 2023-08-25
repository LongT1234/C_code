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
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }
    perror("socket");
    //绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(55555);
    addr.sin_addr.s_addr = inet_addr("192.168.110.162");
    int res = bind(fd,(struct sockaddr *)&addr,sizeof(addr));
    if(res == -1)
    {
        perror("bind");
        return -1;
    }
    perror("bind");
    //接收消息
    char r_buf[100] = {0};
    struct sockaddr_in s_addr;
    socklen_t len = sizeof(s_addr);
    while(1)
    {
        memset(r_buf,0,100);
        recvfrom(fd,r_buf,100,0,(struct sockaddr *)&s_addr,&len);
        perror("recvfrom");
        printf("消息：%s\n",r_buf);
    }
    return 0;
}