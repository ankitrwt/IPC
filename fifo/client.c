#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<limits.h>
#include<string.h>


int main()
{
int fd,ret;
char str[20];

	ret = access("./fifo2",F_OK);
	
	if (ret == -1){
		ret = mkfifo("./fifo2", 0777);
		if (ret != 0)
		{
			fprintf(stderr, "Could not create fifo %s\n", "./fifo2");
			exit(EXIT_FAILURE);
		}
	}

fd = open("fifo2",O_RDONLY);//|O_NONBLOCK);
if(fd == -1)
{
	perror("FIFO open fails\n");
}

ret = read(fd,str,sizeof(str));
printf("%s: Bytes Read %d\n",__FILE__,ret);
printf("%s: %s\n",__FILE__,str);
close(fd);


fd = open("fifo2",O_WRONLY|O_NONBLOCK);
if(fd == -1)
{
	perror("FIFO open fails\n");
}

strcpy(str,"string is changed\n");
ret = write(fd,str,sizeof(str));
printf("%s: Bytes write %d\n",__FILE__,ret);

unlink("fifo2");
return 0;
}
