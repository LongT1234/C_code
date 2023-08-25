#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main()
{
    int msgid = msgget(12345,IPC_CREAT|0777);
    if(msgid == -1)
    {
        perror("msgget");
        return -1;
    }
    printf("msgid=%d\n",msgid);
    return 0;
}