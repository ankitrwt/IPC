#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/un.h>



int main()
{
int sockfd,len,result;
struct sockaddr_un address;
char ch = 'A';

	sockfd = socket(AF_UNIX,SOCK_STREAM,0);

	address.sun_family = AF_UNIX;
	strcpy(address.sun_path,"server_socket");
	len = sizeof(address);
	result = connect(sockfd,(struct sockaddr*)&address,len);
	if(result == -1){
		perror("connect fails\n");
		exit(1);
	}

	write(sockfd,&ch,1);
	read(sockfd,&ch,1);
	printf("server write: %c\n",ch);
	close(sockfd);

return 0;
}
