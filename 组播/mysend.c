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
    
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd==-1)
    {

        perror("socket");
        return -1 ;
    }
     perror("socket");
       struct ip_mreqn o_val;
       char w_buf[1024]={0};
       int num = 100;
       o_val.imr_ifindex = if_nametoindex("ens33");
       o_val.imr_address.s_addr =  INADDR_ANY;
       o_val.imr_multiaddr.s_addr= inet_addr("226.0.0.2");

     setsockopt(fd,IPPROTO_IP,IP_MULTICAST_IF ,&o_val,sizeof(o_val));
         struct sockaddr_in b_addr;
    b_addr.sin_family = AF_INET;
    b_addr.sin_port = htons(12121);
    b_addr.sin_addr.s_addr = inet_addr("226.0.0.2");
     while (1)
     {
         
         
        sprintf(w_buf,"num=%d",num);
        sendto(fd,w_buf,sizeof(w_buf),0,(struct sockaddr *)&b_addr,sizeof(b_addr));
        num++;
        sleep(1);
        printf("发送：%s\n",w_buf);

     }
    return 0 ;
}