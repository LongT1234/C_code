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
    char w_buf[100] = {0};
    //创建管道文件
    int a = mkfifo("a.fifo",0777);
    if(a == -1)
    {
        perror("mkfifo");
    }
    //打开管道文件,只写方式打开
    printf("open前\n");
    int fd = open("a.fifo",O_WRONLY);
    printf("open后\n");
    if(fd == -1)
    {
        perror("open");
    }
    //写
    while (1)
    {
        printf("请输入要向管道写入的内容：\n");
        scanf("%s",w_buf);
        write(fd,w_buf,strlen(w_buf));
    }
    return 0;
}