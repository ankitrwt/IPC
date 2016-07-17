#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
int ret,p[2];
char rfd[4],wfd[4];
char msg[50] = {"HELLO THIS IS DISCRIPTOR PIPE EXAMPLE\n"};

if(pipe(p) == -1)
{
	perror("pipe creation fails\n");
	exit(EXIT_FAILURE);
}
ret = fork();
switch(ret){
case -1:
	printf("%s: ERROR: fork failure\n"__FILE__);
break;
case 0:
	printf("%s: CHILD  pid: %d ppid: %d\n",__FILE__,getpid(),getppid());
	sprintf(rfd,"%d",p[0]);
	sprintf(wfd,"%d",p[1]);
	execl("./01client","01client",rfd,wfd,NULL);
	printf("%s: ERROR: EXCEL FAIL\n"__FILE__);
break;
default:
	printf("%s: PARENT pid: %d ppid: %d\n",__FILE__,getpid(),getppid());
break;
}

ret = write(p[1],msg,sizeof(msg));
printf("%s: Bytes Written %d\n",__FILE__,ret);

return 0;
}
