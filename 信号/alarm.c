#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <signal.h>

int main()
{
    int count = 0;
    pid_t pid = fork();
    if(pid == 0)
    {
        exit(0);
    }
    if(pid > 0)
    {
        alarm(10);
        sleep(5);
        alarm(10);
        while(1)
        {
            printf("你好\n");
            count++;
            sleep(1);
        }
    }
    return 0;
}