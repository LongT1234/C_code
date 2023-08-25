#include <glob.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int i = 0;
    char buf[100] = {0};
    glob_t p = {0};
    glob("/home/zsy/0810/目录操作文件属性作业/*.mp3",0,NULL,&p);
    for(i=0;i<p.gl_pathc;i++)
    {
        printf("%s\n",p.gl_pathv[i]);
    }
    sprintf(buf,"%s",p.gl_pathv[3]);
    execlp("mpg123","mpg123",buf,NULL);
    return 0;
}