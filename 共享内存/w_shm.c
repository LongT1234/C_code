#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    //创建键值
    key_t key = ftok("/",1);
    printf("key1 = %d\n",key);
    //创建共享内存
    int shm = shmget(key,200,IPC_CREAT|0777);
    printf("shm1 = %d\n",shm);
    //映射
    char *p =(char *)shmat(shm,NULL,0);
    //写操作
    strcpy(p,"hello");
    //解除映射
    shmdt(p);
    return 0;
}