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

#define SERVER_PORT 4220			     // arbitrary, but client & server must agree 
#define BUF_SIZE 4096				     // block transfer size

int main(int argc, char *argv)
{
	//variables
	int c, sock, bytes, readSize;
	char msg[BUF_SIZE];				     // buffer for msg
	char returnMsg[BUF_SIZE];
	struct hostent *h;				     // info about server
	struct sockaddr_in channel;			     // holds IP address

	//collect hostname
	if (argc != 3) {printf("Usage: client server-name file-name"); exit(-1);}
	h = gethostbyname(argv);			     // look up host’s IP address
	if (!h) {printf("gethostbyname failed to locate %s", argv[1]); exit(-1;}

	//create socket and connect to the server
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <0) {printf("socket call failed"); exit(-1);}
	memset(&channel, 0, sizeof(channel));
	channel.sin_family= AF_INET;
	memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length);
	channel.sin_port= htons(SERVER_PORT);
	c = connect(sock, (struct sockaddr *) &channel, sizeof(channel));
	if (c < 0) {printf("connect failed"); exit(-1);}

	//Connection is now established. take input from user
	printf("\nInput message to be sent: ");
	scanf("%s", msg);
	
	//write out to server
	write(sock, msg, strlen(msg));
	printf("\nMessage successfully sent.");
	
	//read back from server
	readSize = read(sock, returnMsg, BUF_SIZE);
	write(1, returnMsg, readSize);
	printf("\n\n%s", returnMsg);

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
}
