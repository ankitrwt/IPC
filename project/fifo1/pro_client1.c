#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include"buf.h"


int main(int argc, char **argv)
{
int ret,fd,result;
req cli;

if(argc != 1)
{
	printf("%s INVALID ARGUMENTS\n",__FILE__);
	exit(EXIT_FAILURE);
}
printf("%s pro_client successfully created\n",__FILE__);

fd = open("./pro_fifo",O_RDONLY);
ret = read(fd,&cli,sizeof(cli));
printf("%s bytes read %d, REQUEST: %d %c %d\n",__FILE__,ret,cli.opr1,cli.opr,cli.opr2);
close(fd);
result = cli.opr1 + cli.opr2; 

fd = open("./pro_fifo",O_WRONLY);
ret = write(fd,&result,sizeof(result));
printf("%s bytes write %d, RESULT: %d\n",__FILE__,ret,result);
close(fd);
return 0;
}
