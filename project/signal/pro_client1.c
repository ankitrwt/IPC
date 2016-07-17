#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include"buf.h"


int main(int argc, char **argv)
{
int ret,rfd,wfd,result;
req cli;

if(argc != 3)
{
	printf("%s INVALID ARGUMENTS\n",__FILE__);
	exit(EXIT_FAILURE);
}
printf("%s pro_client successfully created\n",__FILE__);

rfd = atoi(argv[1]);
wfd = atoi(argv[2]);


printf("%s RECEIVED FD READ %d WRITE %d\n",__FILE__,rfd,wfd);
ret = read(rfd,&cli,sizeof(cli));
printf("%s bytes read %d, REQUEST: %d %c %d\n",__FILE__,ret,cli.opr1,cli.opr,cli.opr2);

result = cli.opr1 + cli.opr2; 

ret = write(wfd,&result,sizeof(result));
printf("%s bytes write %d, RESULT: %d\n",__FILE__,ret,result);

kill(getppid(),SIGPIPE);
return 0;
}
