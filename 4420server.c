#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>         /* sockaddr_in */
#include <netdb.h>

#define SERVER_PORT 4220        /* Opening the port on 4220 as it has no 
                                   assignments that is standardized */
#define BUF_SIZE 4096           /* Block transfer size */
#define QUEUE_SIZE 10           /* Max number of pending connections, we'll do 10 just to be safe */

int main(void){

    char buffer[BUF_SIZE];
    struct sockaddr_in local_addr;   /* addr structs */
    int socknet, bindnet, listener, bouncer;            /* socket and bind vars */
    bool open_socket = 1;

    socknet                     = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_net < 0){
        printf("Hey, we're getting an error here!");
        exit(-1);
    }
    
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family       = AF_INET;              /* Matches socket call */
    local_addr.sin_port         = htons(SERVER_PORT);          /* Specify which port to listen on */
    local_addr.sin_addr.s_addr  = htonl(INADDR_ANY);    /* Allow the server to access on any interface */

    bindnet                     = bind(socknet, (struct sockaddr *) &local_addr, sizeof(local_addr)); /* Bind the server */
    if (bindnet < 0) {
        printf("Couldn't bind :(");
        exit(-1);
    }

    listener                    = listen(socknet, QUEUE_SIZE); /* Begin listening for any connections */
    if (listener < 0) {
        printf("Listening failed :(");
        exit(-1);
    }

    while(open_socket) {
        bouncer                     = accept(socknet, 0, 0);
        if (bouncer < 0) {
            printf("The bouncer couldn't let the connection in");
            exit(-1);
        }

        read(bouncer, buffer, BUF_SIZE);

        /*
            Skeleton almost done, to do: Set up the send-back plan.
            Do we want it to send a specific message back by default?
            Maybe edit the string in some way?
        */

       // Add read in here

       while(1) {
            // add the writeback here

       }

       close(bouncer);

    }



}
