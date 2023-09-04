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
#include <sys/epoll.h>
#include <sys/time.h>

void *Fun(void *a);

int main()
{
    //创建套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    perror("socket");
    
    //有的时候会出现端口号被占用的情况，这句话的作用让端口可以被重复使用
    int val = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
    //绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    if(res == -1)
    {
        perror("bind");
        return -1;
    }
    perror("bind");
    //监听
    res = listen(sockfd,50);
    if(res == -1)
    {
        perror("listen");
        return -1;
    }
    perror("listen");
    //创建句柄
    int epfd = epoll_create(1);
    //把连接套接字存入句柄
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);
    int ren = 0;
    struct epoll_event buf[51];
    struct sockaddr_in c_addr;
    socklen_t len = sizeof(c_addr);
    int cfd[50] = {0};
    int count = 0;
    char rw_buf[100] = {0};
    while(1)
    {
        ren = epoll_wait(epfd,buf,51,-1);
        for(int i=0;i<ren;i++)
        {
            //sockfd发生异动
            if((buf[i].data.fd==sockfd)&&(buf[i].events&EPOLLIN))
            {
               cfd[count]=accept(sockfd,(struct sockaddr *)&c_addr,&len);
               printf("%d上线\n",cfd[count]);
               //把通信套接字存入句柄
                ev.events = EPOLLIN;
                ev.data.fd = cfd[count];
                epoll_ctl(epfd,EPOLL_CTL_ADD,cfd[count],&ev);
                count++;
            }
            else if((buf[i].data.fd!=sockfd)&&(buf[i].events&EPOLLIN))
            {
                memset(rw_buf,0,100);
                int re = recv(buf[i].data.fd,rw_buf,100,0);
                //有客户端发来消息
                if(re > 0)
                {
                    //群发
                    for(int j=0;j<count;j++)
                    {
                        //排除自己和已下线的用户
                        if(buf[i].data.fd!=cfd[j])
                        {
                            send(cfd[j],rw_buf,100,0);
                        }
                    }
                }
                //客户端下线
                else if(re == 0)
                {
                    memset(rw_buf,0,100);
                    sprintf(rw_buf,"%d下线",buf[i].data.fd);
                    //群发
                    for(int j=0;j<count;j++)
                    {
                        //排除自己和已下线的用户
                        if(buf[i].data.fd!=cfd[j])
                        {
                            send(cfd[j],rw_buf,100,0);
                        }
                    }
                    //更新cfd数组
                    for(int k=i;k<count-1;k++)
                    {
                        cfd[k] = cfd[k+1];
                    }
                    count--;
                    //把套接字从句柄中删除
                    epoll_ctl(epfd,EPOLL_CTL_DEL,buf[i].data.fd,NULL);
                }
            }
        }
    }
}
