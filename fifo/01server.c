#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>


int main()
{
int ret,fd;
char str[] = "HELLO THIS IS FIFO SERVER\n";

fd = open("./FIFO1",O_WRONLY|O_NONBLOCK);
if(fd == -1)
{	
	printf("Pipe open fails\n");
	exit(1);
}

ret = write(fd,str,sizeof(str));
printf("%s: Bytes write :%d\n",__FILE__,ret);

return 0;
}
