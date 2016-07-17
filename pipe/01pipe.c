#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

int main()
{
int ret,p[2];
char W_buf[BUFSIZ] = "String Written in Pipe\n";
char R_buf[BUFSIZ];

if(pipe(p)==-1)
{
	perror("ERROR: Pipe Not Created\n");
	exit(1);
}

	printf("p[0] = %d\np[1] = %d\n",p[0],p[1]);

	ret = write(p[1],W_buf,25);
//	close(p[1]);
	printf("Bytes Written : %d\n",ret);
//	ret = write(p[1],W_buf,25);
//	printf("Bytes written : %d\n",ret);
//	ret = read(p[0],R_buf,30);
//	strcpy(R_buf,PIPE_BUF);
	printf("%d",PIPE_BUF);

return 0;
}
