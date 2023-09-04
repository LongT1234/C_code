#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

char fun1(char a)
{
    char b = 0;
    if(a == DT_BLK)
        b = 'b';
    if(a == DT_CHR)
        b = 'c';
    if(a == DT_DIR)
        b = 'd';
    if(a == DT_FIFO)
        b = 'f';
    if(a == DT_LNK)
        b = 'l';
    if(a == DT_REG)
        b = '-';
    if(a == DT_SOCK)
        b = 's';
    return b;
}

int main(int argc,char *argv[])
{
    DIR *p = opendir(argv[1]);
    if(p == NULL)
    {
        perror("opendir");
        return -1;
    }
    struct dirent *q = NULL;
    while( (q = readdir(p)) != NULL)
    {
        printf("文件属性：%c 文件名：%s\n",fun1(q->d_type),q->d_name);
    }
    char * id = getcwd(NULL,0);
    printf("当前路径为%s\n",id);
    mkdir("./222",0777);
    chmod("./222",0777);
    chdir("./222");
    id = getcwd(NULL,0);
    printf("跳转后路径为%s\n",id);
    //rmdir("../222");
    closedir(p);
    return 0;
}