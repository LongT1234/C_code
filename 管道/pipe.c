#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
//无名管道写一个代码，子进程写，父进程读。约定子进程写入qiut是父子进程退出
int main()
{
    ssize_t a = 0;
    int fd[2] = {0};
    char w_buf[100] = {0};
    char r_buf[100] = {0};
    pipe(fd);
    pid_t pid = fork();
    //子进程写
    if(pid == 0)
    {
        close(fd[0]);//关闭读端
        while(1)
        {
            scanf("%s",w_buf);
            if(!strcmp(w_buf,"quit"))
                exit(0);
            write(fd[1],w_buf,strlen(w_buf));
            printf("向管道中写入：%s\n",w_buf);
        }
    }
    //父进程读
    if(pid > 0)
    { 
        close(fd[1]);//关闭写端
        while(1)
        {
            a = read(fd[0],r_buf,100);
            if(a == 0)
                return 0;
            printf("从管道中读取到%s\n",r_buf);
        }
    }
    return 0;
}