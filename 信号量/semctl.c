#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

union semun {
    int              val;    /* 信号量的初始值 */
    struct semid_ds *buf;    /* 不用管 */
    unsigned short  *array;  /* 不用管 */
    struct seminfo  *__buf;  /*不用管 */
           };

int main()
{
    int id = semget(1122,1,IPC_CREAT|0777);
    printf("信号量集id:%d\n",id);
    //信号量初始化
    union semun s;
    s.val = 1;//二值信号量
    semctl(id,0,SETVAL,s);
    //查看当前信号量的值
    int n = semctl(id,0,GETVAL);
    printf("信号量的值:%d\n",n);
    //删除信号量
    semctl(id,0,IPC_RMID);
    return 0;
}