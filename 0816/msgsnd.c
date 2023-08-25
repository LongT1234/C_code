#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct msgbuf {
    long mtype;       /* 要写入的消息类型 */
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
    struct msgbuf w_buf;
    printf("请输入要发送的消息类型\n");
    scanf("%ld",&w_buf.mtype);
    printf("请输入要发送的内容\n");
    scanf("%s",w_buf.mtext);
    int a = msgsnd(msgid,&w_buf,sizeof(struct msgbuf)-sizeof(long),0);
    if(a == -1)
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}