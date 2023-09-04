#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int fp = open(argv[1],O_RDWR|O_CREAT|O_EXCL,0777);
    if(fp == -1)
    {
        perror("open");
        return -1;
    }
    close(fp);
    return 0;
}