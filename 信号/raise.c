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
        while(1);
    }
    if(pid > 0)
    {
        while(1)
        {
            printf("你好\n");
            count++;
            sleep(1);
            if(count > 10)
            {
                kill(pid,9);
                raise(9);
            }
        }
    }
    return 0;
}