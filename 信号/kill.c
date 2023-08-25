#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <signal.h>

int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
       while(1)
       {
            printf("hello\n");
            sleep(1);
       }
    }
    if(pid > 0)
    {
        sleep(10);
        kill(pid,9);
    }
    return 0;
}