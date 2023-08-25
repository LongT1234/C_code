#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *fun(void *p);

int main()
{
    pthread_t id = 0;
    pthread_create(&id,NULL,fun,"hello");
    printf("i am main pthread\n");
    pthread_join(id,NULL);
    printf("副线程结束\n");
    return 0;
}

void *fun(void *p)
{
    printf("%d：%s\n",__LINE__,(char *)p);
    sleep(2);
}