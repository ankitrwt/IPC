#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>


int main()
{
char ch[20] = "Hello Server\n";
int sockfd,len;
char chr = 'A';
struct sockaddr_in address;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		printf("ERROR: socket fails\n");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_port   = htons(5004);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	len = sizeof(address);
	if(connect(sockfd,(struct sockaddr *)&address, len) == -1){
		perror("ERROR");
		exit(EXIT_FAILURE);
	}

//	while(1)
	{
	
		write(sockfd,&chr,sizeof(chr));
		//memset(ch,'\0',sizeof(ch));
		//sleep(1);
		read(sockfd,&chr,sizeof(chr));
		printf("server: %c\n",chr);
		//close(sockfd);
	}
return 0;
}
