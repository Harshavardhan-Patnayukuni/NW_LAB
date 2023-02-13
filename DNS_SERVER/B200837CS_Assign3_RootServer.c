#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>
//client 4000
//local dns server 4000
// root dns server 5000
// tld dns server 6000(in) 6001(com)
// authoritative dns server 7000
struct sockaddr_in tld_addr;

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
	char *ip="127.0.0.1";
	int port =atoi(argv[1]);
	int server_sock,client_sock;
	struct sockaddr_in server_addr,local_addr;
	socklen_t addr_size;
	char buffer[1024];
	int n;
	server_sock=socket(AF_INET,SOCK_DGRAM,0);
	if(server_sock<0)
	{
		perror("socket error\n");
		exit(1);
	}
	
	memset(&server_addr,'\0',sizeof(server_addr));
	memset(&local_addr,'\0',sizeof(local_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr.s_addr=inet_addr(ip);
	n=bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(n<0)
	{
		perror("bind error\n");
		exit(1);
	}

	while(1)
	{
        addr_size=sizeof(local_addr);
        bzero(buffer,1024);
        int k=sizeof(local_addr);
        recvfrom(server_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&local_addr,&k);
        printf("client: %s\n",buffer);
        int  root_sock;
        char temp[100];
        strcpy(temp,buffer); 
       // handletld(temp);
        
    tld_addr.sin_family=AF_INET;
    tld_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
        tld_addr.sin_port=htons(6000);
        sendto(server_sock,buffer,strlen(buffer),0,(struct sockaddr*)&tld_addr,k);
        recvfrom(server_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&tld_addr,&k);
        sendto(server_sock,buffer,strlen(buffer),0,(struct sockaddr*)&local_addr,k);
	}
	close(client_sock);
	close(server_sock);


}
