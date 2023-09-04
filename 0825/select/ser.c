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

void *Fun(void *a);
int cfd[3] = {0};
int main()
{
    int maxfd;
    //创建套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1)
    {
        perror("socket");
        return -1;
    }
    maxfd = sockfd;
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
    struct sockaddr_in c_addr;
    socklen_t len = sizeof(c_addr);
    //创建保存套接字的集合
    fd_set readset,bpset;
    //清理集合
    FD_ZERO(&bpset);
    //将套接字加入到集合
    FD_SET(sockfd,&bpset);
    int cdf[50] = {0};
    int ren = 0;
    int count=0,i=0,j=0;
    char buf[100] = {0};
    //select完成多路IO复用
    while (1)
    {
        readset = bpset;
        //阻塞直到有文件描述符发生异动
        ren = select(maxfd+1,&readset,NULL,NULL,NULL);
        //sockfd发生异动，accept
        if(FD_ISSET(sockfd,&readset))
        {
            cfd[count] = accept(sockfd,(struct sockaddr *)&c_addr,&len);
            ///更新最大文件描述符
            if(maxfd < cfd[count])
            {
                maxfd  = cfd[count];
            }
            //更新监听集合
            FD_SET(cfd[count],&bpset);
            count++;
            if(ren == 1)
                continue;
        }
        for(i=0;i<count;i++)
        {
            if(FD_ISSET(cfd[i],&readset))
            {
                memset(buf,0,100);
                int re = recv(cfd[i],buf,100,0);
                //客户端发消息
                if(re > 0)
                {
                    //群发消息
                    for(j=0;j<count;j++)
                    {
                        //屏蔽自己和不在线的用户
                        if(i!=j)
                        {
                            send(cfd[j],buf,100,0);

                        }
                            
                    }
                }
                //客户端下线
                else if(re == 0)
                {
                    FD_CLR(cfd[i],&bpset);
                    sprintf(buf,"%d下线\n",cfd[i]);
                    //群发下线提示
                    for(j=0;j<count;j++)
                    {
                        //屏蔽自己和不在线的用户
                        if(i!=j)
                            send(cfd[j],buf,100,0);
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
    
}
