// server program for udp connection 
#include <stdio.h> 
#include <iostream>
#include <string>

#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include "sql_server_driver.hpp"
#define PORT 7929 
#define MAXLINE 1000 

using namespace std;

// Driver code 
int main() 
{ 

	Database_driver drivep;
	
	err_msg connected = drivep.connect("root","VARZZZ");
 
 schema_creds e;
 e.username="nazriya";
 e.password="varshu";
 e.mobile_number = "9923786299";
 e.status = 1;
  
  err_msg i_success = drivep.insert_creds(e);
	
 
  //bool f_success = drivep.add_friend("varzzz","nazriya");
  
  friends ui = drivep.get_friends_info("nazriya");
  cout << connected.error << " "<<i_success.error<<' '<<ui.error << ' ' << ui.n_online << '\n';
	char buffer[100]; 
  string message = "Hello Client"; 
  
	unsigned int listenfd, len; 
	struct sockaddr_in servaddr, cliaddr; 
	bzero(&servaddr, sizeof(servaddr)); 

	// Create a UDP Socket 
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 

	// bind server address to socket descriptor 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	// char ip[30];
	//receive the datagram 
	while(true)
	{
		len = sizeof(cliaddr); 
		int n = recvfrom(listenfd, buffer, sizeof(buffer), 
				0, (struct sockaddr*)&cliaddr,&len); //receive message from server 

		cout<<(char*)inet_ntoa((struct in_addr)cliaddr.sin_addr)<<endl;
		buffer[n] = '\0';
		puts(buffer); 
	}
} 
