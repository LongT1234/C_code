#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char *argv[])
{
    char r_buf[100] = {0};
    int fp = open(argv[1],O_RDWR|O_CREAT|O_APPEND,0777);
    if(fp == -1)
    {
        perror("open");
        return -1;
    }
    ssize_t n = read(fp,r_buf,100);
    if(n == -1)
    {
        perror("read");
        return -1;
    }
    printf("读出%ld个字节\n读取到的内容为：%s\n",n,r_buf);
    close(fp);
    return 0;
}