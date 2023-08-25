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
    //发送
    char w_buf[100] = {0};
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(55555);
    addr.sin_addr.s_addr = inet_addr("192.168.110.162");
    while(1)
    {
        memset(w_buf,0,100);
        printf("请输入要发送的内容：\n");
        scanf("%s",w_buf);
        getchar();
        sendto(fd,w_buf,sizeof(w_buf),0,(struct sockaddr *)&addr,sizeof(addr));
        perror("sendto");
    }
    return 0;
}