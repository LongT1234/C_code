#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int a = 0;
    printf("hello\n");
    pid_t pid = vfork();
    if(pid == 0)
    {
        a = a+10;
        printf("i am son\n");
        printf("son:a = %d\n",a);
        sleep(10);
        _exit(0);
    }
    if(pid > 0)
    {  
        a++;
        printf("father:a = %d\n",a);
        printf("i am father\n");
    }
    return 0;
}