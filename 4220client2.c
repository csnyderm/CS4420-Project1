/* 
* 
* Author: Kc Livingston
* Purpose: This page contains a client program that sends a user input message. It should then read the message from the server.
* 
*/

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT "4220"			     // arbitrary, but client & server must agree 
#define BUF_SIZE 4096				     // block transfer size

int main(void)
{
	//variables
	int c, sock, bytes_sent, readSize, status;
	char msg[BUF_SIZE];				     // buffer for msg
	char returnMsg[BUF_SIZE];
	struct addrinfo hints;
	struct addrinfo *servinfo;
	
	//set hints for getaddrinfo
	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	//collect hostname
	if ((status = getaddrinfo(NULL, SERVER_PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}
	//if (!h) {printf("gethostbyname failed to locate %d", argv[1]); exit(-1);} // GCC was throwing an error, fixed line, may need additional review

	//create socket and connect to the server
	sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (sock < 0) {printf("socket call failed"); exit(-1);}
	
	
	//connect
	c = connect(sock, servinfo->ai_addr, servinfo->ai_addrlen);
	if (c < 0) {printf("Connect call failed"); exit(-1);}
	
	//read in file
	FILE* inf;
	inf = fopen("text.txt", "r");
	fprintf(stderr, "Opened file");
	
	//check for errors
	if (inf == NULL) {fprintf(stderr, "\nError opening the file\n"); exit(1);}
	
	//read in the file and send it over line by line
 	while (fgets(msg, sizeof msg, inf)){
		fprintf(stderr, "Sending: %s\n", msg);
		send(sock, msg, strlen(msg), 0);
  	}

	//let us know job finished and close the file
  	fprintf(stderr, "Jobs done");
    
  	fclose(inf);
  
	
	
	//close pointers and free memory
	close(sock);
	freeaddrinfo(servinfo);

	return 0;
}
