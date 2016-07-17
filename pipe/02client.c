#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include"info.h"
#include<fcntl.h>

int main(int argc, char **argv)
{
int fd,ret,wfd,rfd;
char W_buf[BUFSIZ] = "String Written in Pipe\n";
char R_buf[BUFSIZ];
struct request cli;

char a;
int b,c;

if(argc != 2)
{
	perror("ERROR: Invalid number of arguments\n");
	exit(1);
}

printf("CLIENT: %s\n",__FILE__);

a = *argv[1];
b = atoi((char *)(argv[1]+1));
c = atoi((char *)(argv[1]+5));

printf(argv[1]);
printf("\na = %c\tb = %d\tc = %d\t\n",a,b,c);

/*
wfd = atoi(argv[1]);
rfd = atoi(argv[2]);

cli.opr = 'A';
cli.opr1= 4;
cli.opr2= 5;

	ret = write(wfd,&cli,sizeof(cli));
	printf("Bytes Written on client: %d\n",ret);
	sleep(1);
	ret = read(rfd,&cli,sizeof(cli));
	printf("Bytes Read on client: %d\nopr = %d",ret,cli.opr);
*/
return 0;
}
