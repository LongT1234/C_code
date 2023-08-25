#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <signal.h>

void FUN(int a)
{
    printf("接收到17号信号\n");
}

int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("i am son\n");
        sleep(5);
        exit(0);
    }
    if(pid > 0)
    {   
        signal(17,FUN);
        pause();
        printf("i am father\n");
    }
    return 0;
}