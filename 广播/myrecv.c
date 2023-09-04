#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int main ()
{
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd == -1)
    {
        perror("socket");
        return -1 ;
    }
     perror("socket");
     struct sockaddr_in addr;
     struct sockaddr_in myaddr;
     socklen_t len = sizeof(myaddr);
     char r_buf[1024]={0};
     addr.sin_family = AF_INET;
    addr.sin_port = htons(12121);
    addr.sin_addr.s_addr= INADDR_ANY;
     bind(fd,(struct sockaddr*)&addr,sizeof(addr));

     while(1)
     {
        memset(r_buf,0,sizeof(r_buf));
        recvfrom(fd,r_buf,sizeof(r_buf),0,(struct sockaddr*)&myaddr,&len);
        printf("接收：%s",r_buf);
        sleep(1);
     }


   

    return 0 ;
}