#include <stdio.h>

#include <netinet/in.h>

#include <stdlib.h>

#include <string.h>

#include <netdb.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <unistd.h>
int main()
{
	printf("welcome ");
	
	char *ip="127.0.0.1";
	
	int port=6600;
	
	int sock;
	
	struct sockaddr_in addr;
	
	socklen_t addr_size;
	
	char input[1024];
	
	int n;
	
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{ perror("socket error");
		exit(1);
	}
	
	memset(&addr,'\0',sizeof(addr));
	
	addr.sin_family=AF_INET;
	
	addr.sin_port=htons(port);
	
	addr.sin_addr.s_addr=inet_addr(ip);

	bzero(input,1024);
	
	char temp[1000];
	
	printf("client: ");
	
	gets(temp);
	
	strcpy(input,temp);
	
	int k=sizeof(addr);
	
	sendto(sock,input,strlen(input),0,(struct sockaddr*)&addr,k);
	
	bzero(input,1024);
	
	int in=recvfrom(sock,input,sizeof(input),0,(struct sockaddr*)&addr,&k);
	
	if(in<0){ printf("error while reading from server");
	}
	
	printf("server: %s\n ",input,in);
	
	
	close(sock);
}
