#include <stdio.h>
#include <netdb.h>

#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include<string.h>

#include <netinet/in.h>

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
     int main()
          {
	printf("welcome\n");
	
	char *ip="127.0.0.1";
	
	int port =6600;
	
	int server_sock,client_sock;
	
	struct sockaddr_in server_addr,client_addr;
	
	socklen_t addr_size;
	
	char input[1024];
	
	int n;
	server_sock=socket(AF_INET,SOCK_STREAM,0);
	if(server_sock<0)
	{ perror("socket error\n");
		exit(1);}
	
	printf("tcp server created\n");
	
	memset(&server_addr,'\0',sizeof(server_addr));
	
	server_addr.sin_family=AF_INET;
	
	server_addr.sin_port=htons(port);
	
	server_addr.sin_addr.s_addr=inet_addr(ip);
	
	n=bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	if(n<0)
	{perror("bind error\n");
		exit(1);
	}
	
	printf("bind to the port %d\n",port);
	
	listen(server_sock,5);
	
	printf("listening\n");
	
	
	addr_size=sizeof(client_addr);
	
	while(1) { 
	client_sock=accept(server_sock,(struct sockaddr*)&client_addr,&addr_size);
	
		printf("client connected\n");
		
		bzero(input,1024);
		
		recv(client_sock,input,sizeof(input),0);
		
		printf("client: %s\n",input);
		

		char *temp=rev(input);
		
		strcpy(input,temp);
		
		send(client_sock,input,strlen(input),0);
		
		
		close(client_sock);
		
		
		printf("client disconnected\n");
	}
	
	close(server_sock);


}
