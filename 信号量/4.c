#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
#include <unistd.h>

int count = 0;

int main()
{
    int id = semget(1122,1,IPC_CREAT|0777);
    printf("信号量集id:%d\n",id);
    //查看当前信号量的值
    int n = semctl(id,0,GETVAL);
    printf("信号量的值:%d\n",n);
    
    //创建共享内存
    int shm = shmget(1111,2000,IPC_CREAT|0777);
    printf("shm1 = %d\n",shm);
    //映射
    char *p =(char *)shmat(shm,NULL,0);
    struct sembuf a;
    char buf[6] = {"+++++"};
    //写操作
    while(1)
    {
        //v操作
        a.sem_num = 0;
        a.sem_op = -1;
        a.sem_flg = 0;
        semop(id,&a,1);
        //向共享内存写
        strcat(p,buf);
        usleep(1000);
        strcat(p,buf);
        //p操作
        a.sem_op = 1;
        semop(id,&a,1);
        count++;
        if(count == 50)
            break;
    }
    //解除映射
    shmdt(p);
    return 0;
}