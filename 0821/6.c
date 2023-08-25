#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *fun(void *a);
void clean_fun(void *a);
int main()
{
    pthread_t id = 0;
    pthread_create(&id,NULL,fun,NULL);
    printf("i am main pthread\n");
    pthread_join(id,NULL);
    return 0;
}

void *fun(void *a)
{
    pthread_cleanup_push(clean_fun,NULL);
    printf("i am son pthread\n");
    pthread_cleanup_pop(0);
}

void clean_fun(void *a)
{
   printf("注册清理函数被调用\n");
}