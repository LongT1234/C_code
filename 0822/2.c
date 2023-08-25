#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int val = 0;
void *Fun(void *p);
//pthread_mutex_t mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int main()
{
    //初始化互斥锁
    //pthread_mutex_init(&mutex,NULL);
    //创建三个副线程
    pthread_t id1,id2,id3;
    pthread_create(&id1,NULL,Fun,NULL);
    pthread_create(&id2,NULL,Fun,NULL);
    pthread_create(&id3,NULL,Fun,NULL);
    //等待三个副线程退出
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);
    pthread_join(id3,NULL);
    //销毁互斥锁
    //pthread_mutex_destroy(&mutex);
    printf("val = %d\n",val);
    return 0;
}

void *Fun(void *p)
{
    int i = 1;
    while(i<=50000)
    {
        pthread_mutex_lock(&lock);
        val = val+1;
        pthread_mutex_unlock(&lock);
        i++;
    }
}