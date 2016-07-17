#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int fork_ret, fd, file_ret,len;
	char str_fd[4];
	char W_buf[BUFSIZ],R_buf[BUFSIZ] = "Hello I want to write things in this file. which name is new_test_file";
	len = strlen(R_buf);
	fd = open("./new_test_file",O_RDWR);
	fork_ret = fork();


	if(file_ret == -1)
	{	
		perror("ERROR IN FILE OPENING");
		goto exit;
	}
	switch(fork_ret)
	{
		case -1:
			printf("ERROR: Fork Failed\n");
			exit(1);
		break;
		case 0:
			//sleep(2);
			if(lseek(fd,0,SEEK_SET) == -1)
			{
				perror("ERROR: lseek fail\n");
				goto exit;
			}
			
			printf("Child: PID: %d, PPID: %d\tFD: %d\n",getpid(),getppid(),fd);
			file_ret = read(fd,W_buf,len);
			sprintf(str_fd,"%d",fd);
			if(execl("./01execl","01execl",str_fd,NULL) == -1)
			{	
				perror("ERROR: execl failed\n");
				goto exit;	
			}
			printf("No of bytes Readed by child : %d\n%s\n",file_ret,W_buf);
		break;
		default:
			//sleep(1);
			printf("Parent: PID: %d, PPID: %d\tFD: %d\n",getpid(),getppid(),fd);
			file_ret = write(fd,R_buf,len);
			printf("No of bytes Written: %d\n",file_ret);
		break;

	}


	//close(fd);
	return 0;

	exit:
		return -1;
}
