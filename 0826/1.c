#include <stdio.h>
#include <mysql/mysql.h>

int main()
{
    //连接数据库
    MYSQL * con = mysql_init(NULL);
    con = mysql_real_connect(con,"localhost","root","1","9207_stu",0,NULL,0);
    if(con == NULL)
    {
        printf("连接失败\n");
        return -1;
    }

    //执行SQL语句(上午给大家讲的指令)，获取表格中的内容。
    char buf[255] = {0};
    sprintf(buf,"select * from infor");
    int res = mysql_query(con,buf);
    if(res != 0)
    {
        printf("获取表格内容失败\n");
        return -1;
    }
    MYSQL_RES *t = mysql_store_result(con);
    int row = 0;
    int column = 0;
    column = mysql_num_fields(t);
    row = mysql_num_rows(t);
    MYSQL_FIELD *b;
    for(int j=0;j<column;j++)
    {
       b = mysql_fetch_field(t);
       printf("%s\t",b->name);
    }
    printf("\n");
    char **a;
    /*for(int i=0;i<row;i++)
    {
       a = mysql_fetch_row(t);
       printf("%s\t",a[i]);
    }*/
    while(a =mysql_fetch_row(t))
    {
       for(int i=0;i<column;i++)
       {
            printf("%s\t",a[i]);
       }
        printf("\n");
    }
    
    //关闭连接
    mysql_close(con);
    return 0;
}