#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include"buf.h"

void sig_hand(int sig_no)
{
	printf("%s: GOT SIGNAL %d\n",__FILE__,sig_no);
}


int main(int argc, char **argv)
{
int ret,rfd,wfd,result;
req cli;

if(argc != 3)
{
	printf("%s INVALID ARGUMENTS\n",__FILE__);
	exit(EXIT_FAILURE);
}
printf("%s client successfully created\n",__FILE__);
signal(SIGINT,sig_hand);

rfd = atoi(argv[1]);
wfd = atoi(argv[2]);

cli.opr = '-';
cli.opr1= 5;
cli.opr2= 6;

printf("%s RECEIVED FD READ %d WRITE %d\n",__FILE__,rfd,wfd);
ret = write(wfd,&cli,sizeof(cli));
printf("%s bytes write %d, REQUEST: %d %c %d = ?\n",__FILE__,ret,cli.opr1,cli.opr,cli.opr2);
kill(getppid(),SIGALRM);
pause();
ret = read(rfd,&result,sizeof(result));
printf("%s bytes read %d,GOT RESULT: %d\n",__FILE__,ret,result);

return 0;
}
