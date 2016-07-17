#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<sys/un.h>

int main()
{
int server_sockfd, client_sockfd;
int server_len,client_len;
struct sockaddr_un server_address;
struct sockaddr_un client_address;

		unlink("server_socket");

		server_sockfd = socket(AF_UNIX		//domain
				,SOCK_STREAM	//type
				,0		//protocol
				);
		if(server_sockfd == -1){
			printf("ERROR: socket fails\n");
			exit(EXIT_FAILURE);
		}

		server_address.sun_family = AF_UNIX;
		strcpy(server_address.sun_path,"server_socket");
		server_len = sizeof(server_address);

		bind(server_sockfd,(struct sockaddr *)&server_address,server_len);


		listen(server_sockfd,5);

		while(1)
		{
			char ch;
			printf("server waiting.....server_sockfd: %d  client_sockfd: %d\n",server_sockfd,client_sockfd);
			client_len = sizeof(client_address);
			client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
			read(client_sockfd,&ch,1);
			ch++;
			write(client_sockfd,&ch,1);
			close(client_sockfd);
		}
return 0;
}
