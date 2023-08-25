#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

int main()
{
    int id1 = semget(1122,1,IPC_CREAT|0777);
    printf("信号量集id1:%d\n",id1);
    int id2 = semget(1123,1,IPC_CREAT|0777);
    printf("信号量集id2:%d\n",id2);
    semctl(id1,0,IPC_RMID);
    semctl(id2,0,IPC_RMID);
    return 0;
}