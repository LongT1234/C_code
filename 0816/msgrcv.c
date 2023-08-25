#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct msgbuf {
    long mtype;       /* 要读出的消息类型 */
    char mtext[100];    /*可以是任意类型 */
};

int main()
{
    int msgid = msgget(12345,IPC_CREAT|0777);
    if(msgid == -1)
    {
        perror("msgget");
        return -1;
    }
    printf("msgid=%d\n",msgid);
    struct msgbuf r_buf;
    long type = 0;
    printf("请读出要读出的消息类型\n");
    scanf("%ld",&type);
    int a = msgrcv(msgid,&r_buf,sizeof(struct msgbuf)-sizeof(long),type,0);
    if(a == -1)
    {
        perror("msgrcv");
        return -1;
    }
    printf("从消息队列中读取到：%s\n",r_buf.mtext);
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}