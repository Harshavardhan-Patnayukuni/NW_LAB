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
// tld dns server 6000
// authoritative dns server 7000
struct cache{
	char name[100];
	char ip[100];
};
struct cache cache[2];
int i=0;
char *lookup(char *str)
{
	for(int j=0;j<=i;j++)
	{
		if(strcmp(str,cache[i].name)==0)
		{
			return cache[i].ip;
		}
	}
	return NULL;
}
void insert(char *name,char *ip)
{
	strcpy(cache[i].ip,ip);
	strcpy(cache[i].name,name);
	i=(i+1)%2;
	
}
int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
	char *ip="127.0.0.1";
	int port =atoi(argv[1]);
	int server_sock,client_sock;
	struct sockaddr_in server_addr,client_addr;
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
	memset(&client_addr,'\0',sizeof(client_addr));
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
        addr_size=sizeof(client_addr);
        bzero(buffer,1024);
        int k=sizeof(client_addr);
        recvfrom(server_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,&k);
        char domain[100];
        strcpy(domain,buffer);
        printf("client: %s\n",buffer);
        char *str=lookup(buffer);
        if(str!=NULL)
        {	
        	//printf("if \n");
        	sendto(server_sock,str,strlen(str),0,(struct sockaddr*)&client_addr,k);
        	continue;
        }
        struct sockaddr_in root_addr;
        int  root_sock;
        root_addr.sin_family=AF_INET;
        root_addr.sin_port=htons(5000);
        root_addr.sin_addr.s_addr=inet_addr(ip);
        sendto(server_sock,buffer,strlen(buffer),0,(struct sockaddr*)&root_addr,k);
        recvfrom(server_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&root_addr,&k);
        insert(domain,buffer);
        sendto(server_sock,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,k);

	}
	close(client_sock);
	close(server_sock);


}
