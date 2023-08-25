#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    //key_t key = ftok("/",1);
    //printf("key2 = %d\n",key);
    int shm = shmget(1111,200,IPC_CREAT|0777);
    printf("shm2 = %d\n",shm);
    return 0;
}