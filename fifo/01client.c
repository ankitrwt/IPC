#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
int ret,fd;
char str[30];

fd = open("./FIFO1",O_RDONLY);//|O_NONBLOCK);
if(fd == -1)
{
	printf("file open fails\n");
	exit(1);
}
ret = read(fd,str,sizeof(str));
printf("%s: Bytes Read: %d\n %s",__FILE__,ret,str);

return 0;
}



