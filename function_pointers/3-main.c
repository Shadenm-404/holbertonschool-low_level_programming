#include <stdio.h>
#include <stdlib.h>
#include "3-calc.h"
int main(int argc,char *argv[]){
	int a,b,res; int (*f)(int,int);
	if(argc!=4){printf("Error\n");exit(98);}
	f=get_op_func(argv[2]);
	if(f==0||argv[2][1]!='\0'){printf("Error\n");exit(99);}
	if((argv[2][0]=='/'||argv[2][0]=='%')&&atoi(argv[3])==0){printf("Error\n");exit(100);}
	a=atoi(argv[1]); b=atoi(argv[3]); res=f(a,b); printf("%d\n",res); return 0;
}
