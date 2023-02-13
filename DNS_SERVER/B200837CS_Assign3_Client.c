#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
	char *ip="127.0.0.1";
	int port =atoi(argv[1]);
	int sock;
	struct sockaddr_in addr;
	socklen_t addr_size;
	char buffer[1024];
	int n;
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("socket error");
		exit(1);
	}
	memset(&addr,'\0',sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);

	bzero(buffer,1024);
	char temp[1000];
	
	gets(temp);
	strcpy(buffer,temp);
	int k=sizeof(addr);
	sendto(sock,buffer,strlen(buffer),0,(struct sockaddr*)&addr,k);
	
	bzero(buffer,1024);
	int in=recvfrom(sock,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,&k);
	
	if(in<0)
	{
		printf("error while reading from server");
	}
	printf("server: %s\n ",buffer);
	
	
	close(sock);
}
