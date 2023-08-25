#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void *fun(void *a);
void fun1(int a);

int main()
{
    //创建线程
    pthread_t id = 0;
    pthread_create(&id,NULL,fun,NULL);
    sleep(10);
    pthread_kill(id,2);
    pthread_join(id,NULL);
    return 0;
}

void *fun(void *a)
{
    signal(2,fun1);
    while(1)
    {
        printf("我是副线程\n");
        sleep(1);
    }
}

void fun1(int a)
{
    printf("%d信号被捕获\n",a);
}