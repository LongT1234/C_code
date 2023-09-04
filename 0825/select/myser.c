#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>

int main()
{


    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        perror("socket");
        return -1;
    }
     //有的时候会出现端口号被占用的情况，这句话的作用让端口可以被重复使用
    int val = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
     perror("socket");
     struct sockaddr_in addr;
     addr.sin_family=AF_INET;
     addr.sin_port = htons(12345);
     addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res= bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
     if(res==-1)
     {
        perror("bind");
        return -1;

     } 
     perror("bind");
     int ret=0;
     ret= listen(sockfd,50);
    if(ret == -1)
    {
        perror("listen");
        return -1;
    }
     perror("listen");
 
     int maxfd ;
     maxfd = sockfd;
     fd_set readfds,bpset;
     int ren = 0;
     int count =0;
     int cfd[50] = {0};
     char r_buf[50]={0};
     char buf[100]={0};
     FD_ZERO(&bpset);
     FD_SET(sockfd, &bpset);
     struct sockaddr_in c_addr;
    socklen_t len = sizeof(c_addr);
   
  
     while (1)
     { 

        //创建需要通信的套接字
        readfds = bpset ;
       ren = select(maxfd+1,&readfds,NULL,NULL,NULL);
       if( FD_ISSET(sockfd,&readfds))  //sockfd异常
       {
        cfd[count]=accept(sockfd,(struct sockaddr *)&c_addr,&len);
        if(maxfd<cfd[count])
        {
            maxfd = cfd[count]; 
        }
        FD_SET(cfd[count], &bpset);  //向集合中添加描述符cfd[count]
        count++;
        if(ren == 1)
        {
            continue;
        }
        
       }
       //拿到套接字进行通信
        for(int i=0 ;i<count;i++)
        { 
            //

            if(FD_ISSET(cfd[i],&readfds))   //异动通信套接字
            {   
                memset(r_buf,0,sizeof(r_buf));               
               
              int rcv=  recv(cfd[i],r_buf,sizeof(r_buf),0);

               printf("r_buf%s\n",r_buf);
               if(rcv > 0)   //有人发消息了
               {
                for(int j=0;j<count;j++)
                {
                    if(j!=i)  //除自己外发送信息
                    {
                        printf("count:%d\n",count);
                        send(cfd[j],r_buf,sizeof(r_buf),0);
                    }


               }

               }  
                
                else if(rcv ==0)
                {
                   FD_CLR(cfd[i], &bpset);
                     sprintf(buf,"%d客户端下线\n",cfd[i]);
                     for(int j=0;j<count;j++)
                       {
                            if(j!=i)  //除自己外发送信息
                             {
                             send(cfd[j],buf,sizeof(buf),0);
                             }

                        }
                         for(int k = i;k<count-1;k++)
                    {
                        cfd[k] = cfd[k+1];
                    }
                        count--;
                        
                


                }
               
 

            

        }
     

       }


     }
     


    return 0 ;
}