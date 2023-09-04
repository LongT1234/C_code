/*************************************************************************
	> File Name: mycp.c
	> Author: zsy
	> Mail: zsy@work.cn 
	> Created Time: 2023年08月08日 星期二 15时16分48秒
 ************************************************************************/

#include <stdio.h>

#include <unistd.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <fcntl.h>


int main(int argc,char *argv[])
{
	char buf[1024]={0};
    int Pt = open(argv[1],O_RDWR);
	int pf = open(argv[2],O_RDWR|O_CREAT|O_TRUNC);
	if(Pt==-1)
	{
	  perror("open error");

	}
	if(pf==-1)
	{
		perror("open error");
	}
	ssize_t  n = read(Pt,buf,1024);
	if(n!=0)
   	{
      if(n<0)
	  {
		  perror("read error");
		  return -1 ;
	  }
          write(pf,buf,n);

	}
close(Pt);
close(pf);
	return 0;
}

