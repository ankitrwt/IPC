#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<limits.h>


int main()
{
int fd,ret;
char str[20] = {"HELLO FIFO EXAMPLE\n"};

	ret = access("./fifo2",F_OK);
	
	if (ret == -1){
		ret = mkfifo("./fifo2", 0777);
		if (ret != 0)
		{
			fprintf(stderr, "Could not create fifo %s\n", "./fifo2");
			exit(EXIT_FAILURE);
		}
	}

fd = open("fifo2",O_WRONLY|O_NONBLOCK);
if(fd == -1)
{
	perror("FIFO open fails\n");
}

ret = write(fd,str,sizeof(str));
printf("%s: Bytes write %d\n",__FILE__,ret);

close(fd);


fd = open("fifo2",O_RDONLY);
if(fd == -1)
{
	perror("FIFO open fails\n");
}
ret = read(fd,str,sizeof(str));
printf("%s: Bytes Read %d\n %s",__FILE__,ret,str);

unlink("fifo2");
return 0;
}
