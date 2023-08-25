#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{
    key_t key = ftok("/",1);
    printf("key2 = %d",key);
    return 0;
}