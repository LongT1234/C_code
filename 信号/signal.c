#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <signal.h>

void FUN(int a)
{
    printf("接收到2号信号\n");
}

int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        exit(0);
    }
    if(pid > 0)
    {
        signal(2,FUN);
        printf("i am father\n");
        while(1);
    }
    return 0;
}