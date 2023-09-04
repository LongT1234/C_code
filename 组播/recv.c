#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <net/if.h>

int main()
{
    //创建套接字UDP
    int fd = socket(AF_INET,SOCK_DGRAM,0); 
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }
    perror("socket");
      struct ip_mreqn  val;
      val.imr_multiaddr.s_addr = inet_addr("226.0.0.2");
      val.imr_address.s_addr = INADDR_ANY;  //本地地址
      val.imr_ifindex = if_nametoindex("ens33");
     setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&val,sizeof(val));

    //绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12121);
    addr.sin_addr.s_addr = inet_addr("226.0.0.2");
    int res = bind(fd,(struct sockaddr *)&addr,sizeof(addr));
    if(res == -1)
    {
        perror("bind");
        return -1;
    }
    perror("bind");
    //接收
    char r_buf[100] = {0};
    struct sockaddr_in b_addr;
    socklen_t len = sizeof(b_addr);
    while(1)
    {
        memset(r_buf,0,100);
        recvfrom(fd,r_buf,100,0,(struct sockaddr *)&b_addr,&len);
        perror("recvfrom");
        printf("消息：%s\n",r_buf);
    }
    return 0 ;
}