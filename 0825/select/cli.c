#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
void *W_Fun(void *a);
int fd = 0;
int main()
{
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }
    printf("fd = %d\n",fd);
    perror("socket");
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(12345);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = connect(fd,(struct sockaddr *)(&ser_addr),sizeof(struct sockaddr));
    if(res == -1)
    {
        perror("connect");
        return -1;
    }
    perror("connect");
    pthread_t id;
    pthread_create(&id,NULL,W_Fun,NULL);
    char r_buf[100] = {0};
    while(1)
    {
        recv(fd,r_buf,sizeof(r_buf),0);
        printf("recv:%s\n",r_buf);
    }
    return 0;
}
void *W_Fun(void *a)
{
    char w_buf[100] = {0};
    while(1)
    {
        printf("请输入要写入的内容：\n");
        scanf("%s",w_buf);
        getchar();
        send(fd,w_buf,sizeof(w_buf),0);
        memset(w_buf,0,100);  
    }   
}


