#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<sys/un.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>

int server_sockfd, client_sockfd,flag;

void sig_hand(int sig_no){

	close(server_sockfd);
//	close(client_sockfd);
	flag = 1;
}

int main()
{
char cha;
char ch[20];	
int server_len,client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

//		unlink("127.0.0.1");
		server_sockfd = socket(AF_INET	//domain
				,SOCK_STREAM	//type
				,0		//protocol
				);
		if(server_sockfd == -1){
			printf("ERROR: socket fails\n");
			exit(EXIT_FAILURE);
		}
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(5004);
		server_address.sin_addr.s_addr = htonl(INADDR_ANY);
		
//		strcpy(server_address.sun_path,"server_socket");
		server_len = sizeof(server_address);
		bind(server_sockfd,(struct sockaddr *)&server_address,server_len);


		listen(server_sockfd,5);
	
		while(!flag)
		{
			printf("server waiting.....\n");	
			client_len = sizeof(client_address);
			client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
			if(client_sockfd == -1){
				perror("ERROR");
				exit(EXIT_FAILURE);
			}
			read(client_sockfd,&cha,sizeof(cha));
			printf("client: %c\n",cha);
			cha = 'Z';
			//strcpy(ch,"Hey client.... \n");
			write(client_sockfd,&cha,sizeof(cha));
		//	close(client_sockfd);
		}
return 0;
}
