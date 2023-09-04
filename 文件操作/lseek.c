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
    off_t n = lseek(fp, 0, SEEK_END);
    printf("文件大小为%ld\n",n);
    close(fp);
    return 0;
}