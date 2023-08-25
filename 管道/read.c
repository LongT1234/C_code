#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    char r_buf[100] = {0};
    int n = access("./a.fifo", F_OK);
    if(n == -1)
    {
        //创建管道文件
        int a = mkfifo("a.fifo",0777);
        if(a == -1)
        {
            perror("mkfifo");
            return -1;
        }
    }
    //打开管道文件,只读方式打开
    int fd = open("a.fifo",O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }
    //读
    while(1)
    {
        memset(r_buf,0,100);
        read(fd,r_buf,100);
        printf("从管道中读到的内容为：%s\n",r_buf);
    }
    
    return 0;
}