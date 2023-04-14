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
#define BUF_SIZE 256				     // block transfer size

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
	
	/*
	memset(&channel, 0, sizeof(channel));
	channel.sin_family= AF_INET;
	memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length);
	channel.sin_port= htons(SERVER_PORT);
	c = connect(sock, (struct sockaddr *) &channel, sizeof(channel));
	if (c < 0) {printf("connect failed"); exit(-1);}
	*/
	
	//bind
	//bind(sock, servinfo->ai_addr, servinfo->ai_addrlen);
	//if (bind < 0) {printf("bind call failed"); exit(-1);}
	
	//connect
	c = connect(sock, servinfo->ai_addr, servinfo->ai_addrlen);
	if (c < 0) {printf("Connect call failed"); exit(-1);}

  /*
	//Connection is now established. take input from user
	printf("\nInput message to be sent: ");
	fgets(msg, BUF_SIZE, stdin);
	
	//write out to server
	//write(sock, msg, strlen(msg));
	bytes_sent = send(sock, msg, strlen(msg), 0);
	printf("\nMessage of %d bytes sent.", bytes_sent);
	printf("\nMessage total length: %ld bytes", strlen(msg));
  */
  
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

  fprintf(stderr, "Jobs done");
    
  fclose(inf);
  
	
	//read back from server
	//readSize = recv(sock, returnMsg, BUF_SIZE, 0);

	/*
		Why is this write call here? Not sure if there's a purpose so leaving it
		It was causing some artifacting returns. Can send screenshots if need be
		For now it's commented out and everything works.
	*/ 
	//write(1, returnMsg, readSize);

	//printf("\n\n%s", returnMsg);

	/*
	// Connection is now established. Send file name including 0 byte at end.
	write(s, argv[2], strlen(argv[2])+1);
	// Go get the file and write it to standard output.
	while (1) {
		 bytes = read(s, buf, BUF_SIZE);		     // read from socket
		 if (bytes <= 0) exit(0);			     // check for end of file
		 write(1, buf, bytes);			     // write to standard output
	}
	*/
	
	//close pointers and free memory
	close(sock);
	freeaddrinfo(servinfo);

	return 0;
}
