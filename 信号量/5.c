#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>
int main()
{
    //创建共享内存
    int shm = shmget(1111,2000,IPC_CREAT|0777);
    printf("shm1 = %d\n",shm);
    //映射
    char *p =(char *)shmat(shm,NULL,0);
    //读操作
    printf("从共享内存中读取到：%s\n",p);
    //解除映射
    shmdt(p);
    //删除共享内存
    shmctl(shm,IPC_RMID,NULL);
    return 0;
}