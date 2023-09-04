#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char *argv[])
{
    int fp = open(argv[1],O_RDWR|O_CREAT|O_APPEND,0777);
    if(fp == -1)
    {
        perror("open");
        return -1;
    }
    ssize_t n = write(fp,argv[2],strlen(argv[2]));
    if(n == -1)
    {
        perror("write");
        return -1;
    }
    printf("写入%ld个字节\n",n);
    close(fp);
    return 0;
}