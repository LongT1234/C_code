#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    int a = 10;
    printf("hello\n");
    pid_t pid = fork();
    if(pid == 0)
    {
        a = a+10;
        printf("son:%d\n",a);
        printf("i am son,my pid is %d\n",getpid());
        printf("my father is %d\n",getppid());
        sleep(10);//秒
    }
    if(pid > 0)
    {
        //wait(NULL);
        waitpid(-1,NULL,0);
        a++;
        printf("father:%d\n",a);
        printf("i am father,my pid is %d\n",getpid());
        printf("i am father,my son is %d\n",pid);
    }
    return 0;
}