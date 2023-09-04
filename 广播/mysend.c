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
    if(fd==-1)
    {
        perror("socket");
        return -1 ;
    }
    perror("socket");
    int val= 1;
    int num=100;
    //设置广播类型，
    setsockopt(fd,SOL_SOCKET,SO_BROADCAST,&val,sizeof(int));
    char w_buf[1024]={0};
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12121);
    addr.sin_addr.s_addr = inet_addr("192.168.67.83 ");
    while(1)
    {
        sprintf(w_buf,"num = %d\n",num);
        num++;
        sendto(fd,w_buf,sizeof(w_buf),0,(struct sockaddr *)&addr,sizeof(addr));
        printf("发送：num = %s",w_buf);
        sleep(1);
    }
    close(fd);

    return 0 ;
}