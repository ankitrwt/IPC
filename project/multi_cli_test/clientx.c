#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include"members.h"
#include<fcntl.h>


int main(int argc,char **argv)
{
int ret, wfd,rfd,sum;
info cli;

if(argc != 3)
{
        perror("ERROR: Invalid number of arguments\n");
        exit(1);
}

printf("CLIENT*: %s\n",__FILE__);

 rfd = atoi(argv[1]);
 wfd = atoi(argv[2]);

 cli.opr = '*';
 cli.opr1= 4;
 cli.opr2= 5;

			
         printf("%s: fd read: %d %d\n",__FILE__,wfd,rfd);
         ret = write(wfd,&cli,sizeof(cli));
         printf("%s: Bytes Written on client+: %d %d %c %d\n",__FILE__,ret, cli.opr1, cli.opr, cli.opr2);
         sleep(1);
         ret = read(rfd,&sum,sizeof(sum));
         printf("%s: Bytes Read on client+: %d\n%s: Got Result = %d\n",__FILE__,ret,__FILE__,sum);                                     
return 0;
}
