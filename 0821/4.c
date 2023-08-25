#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *fun(void *p);

int main()
{
    pthread_t id = 0;
    pthread_create(&id,NULL,fun,"hello");
    printf("副线程%ld\n",id);
    printf("主线程%ld\n",pthread_self());
    printf("i am main pthread\n");
    pthread_join(id,NULL);
    return 0;//在主线程中调用return,结束整个进程
}

void *fun(void *p)
{
    pthread_t id = pthread_self();
    printf("%d：%s\n",__LINE__,(char *)p);
    printf("副线程号为：%ld\n",id);
    pthread_exit(NULL);//在副线程中调用pthread_exit只结束副线程线程,属于正常退出
}