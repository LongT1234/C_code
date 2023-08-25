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
    int val = 1;
    //设置套接字为广播类型
    setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&val,sizeof(int));
    char w_buf[100] = {0};
    struct sockaddr_in b_addr;
    b_addr.sin_family = AF_INET;
    b_addr.sin_port = htons(44444);
    b_addr.sin_addr.s_addr = inet_addr("192.168.110.255");
    int num = 100;
    while(1)
    {
        sprintf(w_buf,"num=%d",num);
        sendto(fd,w_buf,sizeof(w_buf),0,(struct sockaddr *)&b_addr,sizeof(b_addr));
        num++;
        sleep(1);
        printf("发送：%s\n",w_buf);
    }
    return 0 ;
}