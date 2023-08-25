#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
int main()
{
    int id = semget(1122,1,IPC_CREAT|0777);
    printf("信号量集id:%d\n",id);
    //查看当前信号量的值
    int n = semctl(id,0,GETVAL);
    printf("信号量的值:%d\n",n);

    //创建键值
    key_t key = ftok("/",1);
    printf("key1 = %d\n",key);
    //创建共享内存
    int shm = shmget(key,200,IPC_CREAT|0777);
    printf("shm1 = %d\n",shm);
    //映射
    char *p =(char *)shmat(shm,NULL,0);
    //v操作
    struct sembuf a;
    a.sem_num = 0;
    a.sem_op = -1;
    a.sem_flg = 0;
    semop(id,&a,1);
    n = semctl(id,0,GETVAL);
    //读操作
    printf("从共享内存中读取到：%s\n",p);
    //p操作
    a.sem_op = 1;
    semop(id,&a,1);
    n = semctl(id,0,GETVAL);
    //解除映射
    shmdt(p);
    //删除共享内存
    shmctl(shm,IPC_RMID,NULL);
    return 0;
}