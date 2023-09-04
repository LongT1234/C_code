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
       o_val.imr_ifindex = if_nametoindex("ens33");
       o_val.imr_address.s_addr =  INADDR_ANY;
       o_val.imr_multiaddr.s_addr= inet_addr("226.0.0.2");

     setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&o_val,sizeof(o_val));
     struct sockaddr_in addr;
      struct sockaddr_in myaddr;
      socklen_t len = sizeof(myaddr);
     char r_buf[1024]={0};
     addr.sin_family = AF_INET;
     addr.sin_port = htons(12121);
     addr.sin_addr.s_addr = inet_addr("226.0.0.2");
   int res=  bind(fd,(struct sockaddr *)&addr,sizeof(addr));
    if(res == -1)
    {
        perror("bind");
        return -1;
    }
     perror("bind");
     while (1)
     {
         
         memset(r_buf,0,1024);
        
       recvfrom(fd,r_buf,sizeof(r_buf),0,(struct sockaddr *)&myaddr,&len);
       printf("接收：%s\n",r_buf); 
       sleep(1);
     }
    return 0 ;
}