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
struct details{
    char name[100];
    char ip[100];
};
struct details table[100];
char retip[100]="error wrong domian address";
void handle(char *str)
{
    for(int i=0;i<3;i++)
    {
        if(strcmp(table[i].name,str)==0)
        {
            strcpy(retip,table[i].ip);
            return;
        }
    }
}
int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
    strcpy(table[0].name,"www.pqr.com");
    strcpy(table[0].ip,"192.123.54.1");
    strcpy(table[1].name,"www.abc.com");
    strcpy(table[1].ip,"196.201.23.0");
    strcpy(table[2].name,"www.xyz.in");
    strcpy(table[2].ip,"200.255.67.89");
    
	char *ip="127.0.0.1";
	int port =atoi(argv[1]);
	int server_sock,client_sock;
	struct sockaddr_in server_addr,tld_addr;
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
	memset(&tld_addr,'\0',sizeof(tld_addr));
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
        addr_size=sizeof(tld_addr);
        bzero(buffer,1024);
        int k=sizeof(tld_addr);
        recvfrom(server_sock,buffer,sizeof(buffer),0,(struct sockaddr*)&tld_addr,&k);
        printf("client: %s\n",buffer);
        handle(buffer);
        printf("return ip: %s\n",retip);
        sendto(server_sock,retip,strlen(retip),0,(struct sockaddr*)&tld_addr,k);
        strcpy(retip,"error wrong domain address");
            
	}
	close(client_sock);
	close(server_sock);
}
