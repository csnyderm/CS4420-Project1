#include <sys/types.h>                               /* This is the server code */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER PORT 8080                             /* arbitrar y, but client & server must agree */
#define BUF SIZE 4096                                /* block transfer size */
#define QUEUE SIZE 10

int main(int argc, char *argv[])
{ int s, b, l, fd, sa, bytes, on = 1;
  char buf[BUF SIZE];                                /* buffer for outgoing file */
  str uct sockaddr in channel;                       /* holds IP address */

  /* Build address structure to bind to socket. */
  memset(&channel, 0, sizeof(channel));              /* zero channel */
  channel.sin family = AF INET;
  channel.sin addr.s addr = htonl(INADDR ANY);
  channel.sin por t = htons(SERVER PORT);

  /* Passive open. Wait for connection. */
  s = socket(AF INET, SOCK STREAM, IPPROTO TCP);        /* create socket */
  if (s < 0) {printf("socket call failed0); exit(-1);}
  setsockopt(s, SOL SOCKET, SO REUSEADDR, (char *) &on, sizeof(on));
  
  b = bind(s, (str uct sockaddr *) &channel, sizeof(channel));
  if (b < 0) {printf("bind failed0); exit(-1);}
  
  l = listen(s, QUEUE SIZE);                         /* specify queue size */
  if (l < 0) {printf("listen failed0); exit(-1);}
  
  /* Socket is now set up and bound. Wait for connection and process it. */
  while (1) {
      sa = accept(s, 0, 0);                          /* block for connection request */
      if (sa < 0) {printf("accept failed0); exit(-1);}
      
      read(sa, buf, BUF SIZE);                       /* read file name from socket */
      
      /* Get and return the file. */
      fd = open(buf, O RDONLY);                      /* open the file to be sent back */
      if (fd < 0) {printf("open failed");

      while (1) {

           bytes = read(fd, buf, BUF SIZE); /* read from file */
           if (bytes <= 0) break;                    /* check for end of file */
           wr ite(sa, buf, bytes);                   /* wr ite bytes to socket */
      }
      close(fd);                                     /* close file */
      close(sa);                                     /* close connection */
  }
}
