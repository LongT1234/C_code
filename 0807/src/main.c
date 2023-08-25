#include "main.h"

int main(int argc,char *argv[])
{
	if(argc < 4)
	{
		printf("传入参数错误\n");
		return -1;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[3]);
	switch(*argv[2])
	{
		case '+':FUN_ADD(a,b);break;
		case '-':FUN_SUB(a,b);break;
		case 'x':;break;
		case '/':;break;
	}
	return 0;
}
