#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//静态创建互斥锁
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//定义一个全局的条件变量
pthread_cond_t cond;

void *fun1(void *p);
void *fun2(void *p);

int main()
{
    //初始化条件变量
    pthread_cond_init(&cond,NULL);
    //创建线程
    pthread_t id1,id2;
    pthread_create(&id1,NULL,fun1,NULL);
    pthread_create(&id2,NULL,fun2,NULL);
    //线程等待函数
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    //销毁互斥锁和条件变量
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}

void *fun1(void *p)
{
    printf("小红在等车\n");
    pthread_cond_wait(&cond,&lock);
    printf("上车，出发\n");
}

void *fun2(void *p)
{
    sleep(10);
    printf("车到了\n");
    pthread_cond_signal(&cond);
}