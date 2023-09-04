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
	struct tm *p  = gmtime(&t);
	printf("%d-%d-%d   %d:%d:%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday, p->tm_hour,p->tm_min,p->tm_sec);
	return 0;
}

