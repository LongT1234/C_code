#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *fun(void *a);

int main()
{
    pthread_t id = 0;
    pthread_create(&id,NULL,fun,NULL);
    printf("i am main pthread\n");
    sleep(10);
    pthread_cancel(id);
    pthread_join(id,NULL);
    printf("副线程已被取消\n");
    return 0;
}

void *fun(void *a)
{
    while(1)
    {
        printf("i am son pthread\n");
        sleep(1);
    }
    pthread_exit(NULL);
}