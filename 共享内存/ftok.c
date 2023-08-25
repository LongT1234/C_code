#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main()
{
    key_t key = ftok("/",1);
    printf("key1 = %d",key);
    return 0;
}