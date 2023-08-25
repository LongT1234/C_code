#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid = vfork();
    if(pid == 0)
    {
        printf("i am son,my pid is %d\n",getpid());
        execlp("ls","ls","-a","-l",NULL);
        printf("nihao\n");
        printf("111111\n");
        _exit(0);
    }
    if(pid > 0)
    {  
        printf("i am father\n");
    }
    return 0;
}