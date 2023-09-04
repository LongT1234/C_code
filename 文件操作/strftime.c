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
	 char buf[100]={0};
    time_t t = time(NULL);
	struct tm* q = localtime(&t);
    strftime(buf,100,"%c",q);
	printf("%s\n",buf);
	return 0;
}

