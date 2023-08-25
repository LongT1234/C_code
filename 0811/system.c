#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid = vfork();
    if(pid == 0)
    {
        printf("i am son\n");
        system("./hello");
        sleep(10);
        _exit(0);
    }
    if(pid > 0)
    {  
        printf("i am father\n");
    }
    return 0;
}