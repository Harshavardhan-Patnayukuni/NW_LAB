#include <stdio.h>


#include <netinet/in.h>

#include <sys/types.h>

#include <stdlib.h>

#include <sys/socket.h>


#include <unistd.h>

#include <netdb.h>

#include <string.h>
int main()
{
	printf("welcome ");
	
	char *ip="127.0.0.1";
	
	int port= 6600;
	
	int sock;
	
	struct sockaddr_in addr;
	
	
	socklen_t addr_size;
	
	char input[1024];
	
	int n;
	
	sock=socket(AF_INET,SOCK_STREAM,0);
	
	if(sock<0)
	{ perror("socket error");
		exit(1);
	}
	
	printf("tcp server created\n");
	
	memset(&addr,'\0',sizeof(addr));
	
	addr.sin_family=AF_INET;
	
	addr.sin_port=htons(port);
	
	addr.sin_addr.s_addr=inet_addr(ip);
	
	connect(sock,(struct sockaddr*)&addr,sizeof(addr));
	
	printf("connected to server\n");
	
	bzero(input,1024);
	
	char temp[1000];
	
	printf("client: ");
	
	gets(temp);
	
	strcpy(input,temp);
	
	send(sock,input,strlen(input),0);
	
	bzero(input,1024);
	
	int num =recv(sock,input,999,0);
	
	if(num<0) {printf("error while reading from server");
	}
	
	printf("server: %s\n ",input,num);
	
	close(sock);
	
	printf("disconnected from servere");
}
