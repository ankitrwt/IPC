#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
//#include"info.h"

struct request{

	char opr;
	int opr1;
	int opr2;
};


int main()
{
int len, ret,p[2];
char W_buf[BUFSIZ] = "String Written in Pipe\n";
char R_buf[BUFSIZ],wfd[4],rfd[4];
struct request ser;
len = sizeof(ser);
char str[12];

if(pipe(p)==-1)
{
	perror("ERROR: Pipe Not Created\n");
	exit(1);
}

	printf("p[0] = %d\np[1] = %d\n",p[0],p[1]);

ret = fork();
	switch(ret)
	{
		case -1:
			printf("ERROR: fork failed\n");
		break;
		case 0:
			ser.opr = 'A';
			ser.opr1= 12;
			ser.opr2= 15;
//			sprintf(wfd,"%d",p[1]);
			sprintf(str,"%c",ser.opr);
			//printf("opr = %c\nopr1 = %d\nopr2 = %d\n",ser.opr,ser.opr1,ser.opr2);
			printf("str : %c",str[12]);
			while(1);
			//execl("./01client","01client",str,NULL);
			//printf("ERROR: excel failed\n");
		break;
		default:
/*			printf("SERVER: %s\n",__FILE__);
			ret = read(p[0],&ser,sizeof(ser));
			printf("Bytes Read on server: %d\n\n",ret);
			printf("opr= %c\nopr1 = %d\nopr2 = %d\n",ser.opr,ser.opr1,ser.opr2);
			ser.opr = ser.opr1 + ser.opr2;
			ret = write(p[1],&ser,sizeof(ser)); 
			printf("Bytes written server: %d\n",ret);
*/			while(1);
		break;
	}

close(p[0]);
close(p[1]);
printf("Main Exit\n");
return 0;
}
