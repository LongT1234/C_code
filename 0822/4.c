#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int val = 0;
sem_t sem;
int value;

void *fun(void *p);

int main()
{
    //创建信号量
    sem_init(&sem,0,1);
    //获取信号量的值
    sem_getvalue(&sem,&value);
    //创建线程
    pthread_t id1,id2,id3;
    pthread_create(&id1,NULL,fun,NULL);
    pthread_create(&id2,NULL,fun,NULL);
    pthread_create(&id3,NULL,fun,NULL);
    //线程等待函数
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    pthread_join(id3,NULL);
    //销毁信号量
    sem_destroy(&sem);
    printf("val = %d\n",val);
    return 0;
}

void *fun(void *p)
{
    int i = 1;
    while(i<=50000)
    {
        sem_wait(&sem);//-1
        val = val + 1;
        sem_post(&sem);//+1
        i++;
    }
}




