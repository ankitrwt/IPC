#include<stdio.h>



int main(int argc,char *argv[])
{
char R_buf[BUFSIZ],len;
int fd;
 
fd = atoi(argv[1]);
lseek(fd,0,SEEK_SET);
len = read(fd,R_buf,70);
printf("Execl Success: PID: %d, PPID: %d, FD: %d\n",getpid(),getppid(),fd);
printf("No of bytes Read From execl: %d\n",len);
printf("%s\n",R_buf);
return 0;

}
