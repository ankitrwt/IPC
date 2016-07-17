#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include"members.h"
#include<fcntl.h>


int main(int argc,char **argv)
{
int ret,wfd,rfd,sum;
info cli;

if(argc != 3)
{
        perror("ERROR: Invalid number of arguments\n");
        exit(1);
}

printf("PRO_CLIENTM: %s\n",__FILE__);

 rfd = atoi(argv[1]);
 wfd = atoi(argv[2]);

	 printf("%s: fd read: %d  %d\n",__FILE__,rfd,wfd);
         ret = read(rfd,&cli,sizeof(cli));
         printf("%s: Bytes Read on pro_clieint+: %d\nopr = %c\nopr1 = %d\nopr2 = %d\n",__FILE__ , ret,cli.opr,cli.opr1,cli.opr2);
	 sum = cli.opr1 - cli.opr2;
         ret = write(wfd,&sum,sizeof(sum));
         printf("%s: Bytes Written on pro_client+: %d\n Sum: %d\n", __FILE__, ret,sum);
	                                     
return 0;
}
