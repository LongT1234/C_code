#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
 #include <net/if.h>


int main ()
{
    int fd = socket(AF_INET,SOCK_DGRAM,0);
     if(fd == -1)
     {
        perror("socket");
        return 0 ;
     }
     perror("socket");
      struct ip_mreqn  val;
      val.imr_multiaddr.s_addr = inet_addr("226.0.0.2");
      val.imr_address.s_addr = INADDR_ANY;
      val.imr_ifindex = if_nametoindex("ens33");
     setsockopt(fd,IPPROTO_IP,IP_MULTICAST_IF,&val,sizeof(val));
     char w_buf[100] = {0};
    struct sockaddr_in b_addr;
    b_addr.sin_family = AF_INET;
    b_addr.sin_port = htons(12121);
    b_addr.sin_addr.s_addr = inet_addr("226.0.0.2");
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