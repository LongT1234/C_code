#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

char fun1(mode_t c)
{
    char a = 0;
    switch (c & S_IFMT) {
           case S_IFBLK:a='b';break;
           case S_IFCHR:a='c';break;
           case S_IFDIR:a='d';break;
           case S_IFIFO:a='f';break;
           case S_IFLNK:a='l';break;
           case S_IFREG:a='-';break;
           case S_IFSOCK:a='s';break;
           default:printf("unknown?\n");break;
           }
    return a;
}

void fun2(mode_t c)
{
    char buf[10] ={"---------"};
    if(c&S_IRUSR)
        buf[0] = 'r';
    if(c&S_IWUSR)
        buf[1] = 'w';
    if(c&S_IXUSR)
        buf[2] = 'x';
    if(c&S_IRGRP)
        buf[3] = 'r';
    if(c&S_IWGRP)
        buf[4] = 'w';
    if(c&S_IXGRP)
        buf[5] = 'x';
    if(c&S_IROTH)
        buf[6] = 'r';
    if(c&S_IWOTH)
        buf[7] = 'w';
    if(c&S_IXOTH)
        buf[8] = 'x';
    printf("%s",buf);
}

int main()
{
    struct stat statbuf = {0};
    stat("./stat.c",&statbuf);
    printf("%c",fun1(statbuf.st_mode));
    fun2(statbuf.st_mode);
    printf(" %ld ",statbuf.st_nlink);
    printf("%ld ",statbuf.st_size);
    char * p = ctime(&statbuf.st_mtime);//固定格式的字符串会自动还行，所以应该用locaitime或strftime转换
    printf("%s ",p);
    printf("./stat.c\n");
    return 0;
}