#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include"info.h"


int main()
{
int len, ret,p[2];
char W_buf[BUFSIZ] = "String Written in Pipe\n";
char R_buf[BUFSIZ],wfd[4],rfd[4];
struct request ser;
if(pipe(p)==-1)
{
	perror("ERROR: Pipe Not Created\n");
	exit(1);
}

	printf("p[0] = %d\np[1] = %d\n",p[0],p[1]);
//	ret = write(p[1],W_buf,25);
//	close(p[1]);
//	printf("Bytes Written : %d\n",ret);
//	ret = write(p[1],W_buf,25);
//	printf("Bytes written : %d\n",ret);
//	ret = read(p[0],R_buf,30);
//	strcpy(R_buf,PIPE_BUF);
//	printf("%d",PIPE_BUF);

ret = fork();
	switch(ret)
	{
		case -1:
			printf("ERROR: fork failed\n");
		break;
		case 0:
			sprintf(wfd,"%d",p[1]);
			sprintf(rfd,"%d",p[0]);
			execl("./client","client",wfd,rfd,NULL);
			printf("ERROR: excel failed\n");
		break;
		default:
			printf("SERVER: %s\n",__FILE__);
			ret = read(p[0],&ser,sizeof(ser));
			printf("Bytes Read on server: %d\n\n",ret);
			printf("opr= %c\nopr1 = %d\nopr2 = %d\n",ser.opr,ser.opr1,ser.opr2);
			ser.opr = ser.opr1 + ser.opr2;
			ret = write(p[1],&ser,sizeof(ser)); 
			printf("Bytes written server: %d\n",ret);
			while(1);
		break;
	}

close(p[0]);
close(p[1]);
printf("Main Exit\n");
return 0;
}
