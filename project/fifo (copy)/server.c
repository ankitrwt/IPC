#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include"buf.h"

#define MAX_USR 3
req got_data;

int main()
{
int ret,fd;

if(access("./fifo",F_OK) == -1)
{
	if(mkfifo("./fifo",0777) != 0)
	{
		perror("fifo fails\n");
		exit(EXIT_FAILURE);
	}
}

while(1)
{
	fd = open("fifo",O_RDONLY);//|O_NONBLOCK);
	if(fd == -1){
		printf("ERROR: fifo open fails\n");
	}
	ret = read(fd,&got_data,sizeof(got_data));
	printf("%s: read %d bytes from %d\n",__FILE__,ret,got_data.pid);
	close(fd);
	sleep(1);
}

return 0;
}

