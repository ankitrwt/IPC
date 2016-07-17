#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
int ret;
int rfd,wfd;
char buf[50];

if(argc != 3)
{
	printf("%s: INVALID NUMBER OF ARGUMENTS\n",__FILE__);
	exit(EXIT_FAILURE);
}

printf("%s: CHILD CREATION SUCCESS\n",__FILE__);

rfd = atoi(argv[1]);
wfd = atoi(argv[2]);
printf("%s: fd received rfd %d wfd %d\n",__FILE__,rfd,wfd);

ret = read(rfd,buf,sizeof(buf));
printf("%s: Byte Read %d\nMSG: %s\n",__FILE__,ret,buf);

return 0;
}
