#include <stdio.h>


#include <netinet/in.h>

#include <stdlib.h>

#include <string.h>

#include <netdb.h>

#include <unistd.h>

#include <sys/socket.h>

#include <sys/types.h>

#include<string.h>

char *rev(char *s){
          char *a, *b;

      if (! s || ! *s)
            return s;
      for (a = s, b = s + strlen(s) - 1;b > a; ++a, --b){
            *a ^= *b;
            *b ^= *a;
            *a ^= *b;}
      return s;
}
     
    int main(){

	printf("welcome\n");
	
	char *ip="127.0.0.1";
	
	int port =6600;
	
	int server_sock,client_sock;
	
	struct sockaddr_in server_addr,client_addr;
	
	socklen_t addr_size;
	
	char input[1024];
	
	int n;
	
	server_sock=socket(AF_INET,SOCK_DGRAM,0);
	
	if(server_sock<0)
	{perror("socket error\n");
		exit(1);
	}
	
	printf("UDP server created\n");
	
	memset(&server_addr,'\0',sizeof(server_addr));
	
	memset(&client_addr,'\0',sizeof(client_addr));
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	
	server_addr.sin_addr.s_addr=inet_addr(ip);
	
	n=bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	if(n<0)
	{ perror("bind error\n"); exit(1);
	}
	
	printf("bind to the port %d\n",port);

	while(1) {
	
	addr_size=sizeof(client_addr);
	
	bzero(input,1024);
	
	int k=sizeof(client_addr);
	
	recvfrom(server_sock,input,sizeof(input),0,(struct sockaddr*)&client_addr,&k);
	
	printf("client: %s\n",input);

	char *temp=rev(input);
	
	strcpy(input,temp);
	
	sendto(server_sock,input,strlen(input),0,(struct sockaddr*)&client_addr,k);
	
	}
	close(client_sock);
	
	close(server_sock);


}
