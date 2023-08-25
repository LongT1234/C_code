#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

sem_t sem;
int value;

void *fun(void *p);

int main()
{
    int i = 0;
    int j = 0;
    //创建信号量
    sem_init(&sem,0,2);
    //获取信号量的值
    sem_getvalue(&sem,&value);
    //创建线程
    pthread_t id[11];
    for(i=0;i<11;i++)
    {
        pthread_create(&id[i],NULL,fun,(void *)i);
    }
    //线程等待函数
    for(j=0;j<11;j++)
    {
        pthread_join(id[j],NULL);
    }
    //销毁信号量
    sem_destroy(&sem);
    
    return 0;
}

void *fun(void *p)
{
    sem_wait(&sem);//-1
    printf("第%d个人正在买票\n",(int)p);
    sleep(1);
    sem_post(&sem);//+1
}




