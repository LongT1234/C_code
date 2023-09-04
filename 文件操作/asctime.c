/*************************************************************************
	> File Name: time.c
	> Author: zsy
	> Mail: zsy@work.cn 
	> Created Time: 2023年08月08日 星期二 14时16分13秒
 ************************************************************************/

#include <stdio.h>
#include<time.h>

int main(int argc,char *argv[])
{
    time_t t = time(NULL);
	struct tm* q = localtime(&t);
	char *p  = asctime(q);
	printf("%s\n",p);
	return 0;
}

