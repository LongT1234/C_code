#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *fun(void *p);

int main()
{
    pthread_t id = 0;
    pthread_create(&id,NULL,fun,"hello");
    printf("i am main pthread\n");
    //pthread_join(id,NULL);
    sleep(5);
    //return 0;//在主线程中调用return,结束整个进程
    pthread_exit(NULL);//在主线程中调用pthread_exit，只结束主线程
}

void *fun(void *p)
{
    printf("%d：%s\n",__LINE__,(char *)p);
    while(1)
    {
        printf("主线程结束\n");
        sleep(2);
    }
    return 0;//在副线程中调用return,只结束副线程
    //pthread_exit(NULL);//在副线程中调用pthread_exit只结束副线程线程,属于正常退出
}