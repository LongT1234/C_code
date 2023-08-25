#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

pthread_t main_id = 0;
pthread_t son_id = 0;

void *fun(void *a);
void clean_fun(void *a);
int main()
{
    
    pthread_create(&son_id,NULL,fun,NULL);
    main_id = pthread_self();
    printf("i am main pthread\n");
    sleep(10);
    pthread_kill(son_id,9);
    pthread_join(son_id,NULL);
    printf("副线程已被杀死\n");
    return 0;
}

void *fun(void *a)
{
    pthread_cleanup_push(clean_fun,NULL);
    while (1)
    {
        printf("i am son pthread\n");
        sleep(1);
    }
    pthread_cleanup_pop(0);
}

void clean_fun(void *a)
{
   printf("注册清理函数被调用\n");
}