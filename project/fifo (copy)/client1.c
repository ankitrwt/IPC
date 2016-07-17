#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include"buf.h"


int main()
{
int ret,result,fd;
req cli;

cli.opr = '+';
cli.opr1= 5;
cli.opr2= 6;
cli.pid = getpid();

	ret = access("./fifo",F_OK);
	if(ret == -1)
	{
		ret = mkfifo("fifo",0777);
		if(ret == -1)
		{
			printf("ERROR: mkfifo fails\n");
			exit(EXIT_FAILURE);
		}
	}

fd = open("fifo",O_WRONLY);
if(fd == -1)
{
	printf("ERROR: fifo open fails\n");
	exit(EXIT_FAILURE);
}
ret = write(fd,&cli,sizeof(cli));
printf("%d bytes write: %d\n",getpid(),ret);
close(fd);

fd = open("fifo",O_RDONLY);
if(fd == -1)
{
	printf("ERROR: fifo open fails\n");
	exit(EXIT_FAILURE);
}
ret = read(fd,&result,sizeof(result));
printf("%d bytes read: %d & GOT: %d %c %d = %d\n",getpid(),ret,cli.opr1,cli.opr,cli.opr2,result);
close(fd);

unlink("fifo");
return 0;
}


