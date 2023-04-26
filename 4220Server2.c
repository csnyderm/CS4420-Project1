/*
    4220 Server developed by Cole Snyder
    This program opens a socket and reads in a file sent by the client.
*/

#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>         /* sockaddr_in */
#include <netdb.h>
#include <unistd.h>
#include <poll.h>

#define SERVER_PORT "4220"        /* Opening the port on 4220 as it has no 
                                   assignments that is standardized */
#define BUF_SIZE 4096         /* Block transfer size */
#define QUEUE_SIZE 10           /* Max number of pending connections, we'll do 10 just to be safe */

int main(void){

    int sock_ear, sock_connect; // Sock_ear listens, while sock_connect takes in new connections
    struct addrinfo hints, *servinfo, *possible;
    struct sockaddr_storage connector_addr; // Connector's addr info
    socklen_t sin_size; // Size of the connector's address
    int addrerror, binding, listener, senderr;
    /*, recverr;*/ // No longer need it for this
    int reuse_port = 1;

    char receive_buf[BUF_SIZE], send_buf[BUF_SIZE];
    
    FILE *receiving_file;


    /* Set up our family to be IPV4, use the TCP Stream socket, and passively use our own IP */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    /* Pull the info into getaddrinfo. addrinfo checks for errors, servinfo holds the result assuming no errors*/
    addrerror = getaddrinfo(NULL, SERVER_PORT, &hints, &servinfo);
    if(addrerror != 0){
        perror("getaddrinfo: Failure ");
        return 1;
    }

    /* 
        Getaddrinfo pulls one or more addrinfo structures. Why? From man page on when it can pull multiple:

        the network host is multihomed, accessible over multiple protocols (e.g., both
        AF_INET and AF_INET6); or the same service is available from multiple socket types
     */

    /* Now we check each possible results and bind to our first that can succeed */
    for(possible = servinfo; possible != NULL; possible = possible->ai_next){

        /* Our first check is to see if we can actually get a socket and if it has any errors */
        sock_ear = socket(possible->ai_family, possible->ai_socktype, possible->ai_protocol);
        if(sock_ear == -1){
            perror("Server Error: Error in the socket initialization");
            continue; // Try the next socket instead, this one doesn't work
        }

        /* Second, if something is already using the port, we want to allow for re-use */
        if(setsockopt(sock_ear, SOL_SOCKET, SO_REUSEADDR, &reuse_port, sizeof(int)) == -1){
            perror("Error in setsockopt");
            exit(1); // If we can't re-use the port for whatever reason, get outa there!
        }

        /* Third and finally, we will try to actually bind */
        binding = bind(sock_ear, possible->ai_addr, possible->ai_addrlen);
        if(binding == -1){
            close(sock_ear); // Close first for safety
            perror("Server Error: Error in the binding initialization");
            continue; // Try the next socket instead
        }

        // Sanity check
        if(possible == NULL){
            perror("Server Error: Failed to bind");
        }

        break; // If none of the previous tests go off, that means we have our socket bound correctly

    }

    freeaddrinfo(servinfo); // Done its job, time to free it from memory

    // Now we check our listener
    listener = listen(sock_ear, QUEUE_SIZE);
    if(listener == -1){
        perror("Server Error: Error in the listener initialization");
        exit(1);
    }

    printf("Server is all set up and waiting for connections! \n");

    /*
        Now we can start checking for connections.
        Each loop, we will try to accept a connection and handle their needs before moving on
        Specifically, we'll take in their message and send one in return.
    */
    while(1) {
        sin_size = sizeof connector_addr;
        sock_connect = accept(sock_ear, (struct sockaddr *)&connector_addr, &sin_size);

        // If this connection doesn't work, we'll go to the next one
        if(sock_connect == -1){
            perror("Server Error: Error in accepting new connection");
            continue;
        }

        printf("Server got a new connection! Waiting on their message now \n");

        /*
            Note of learning from Beej:
            If we want to have multiple connections, we should use fork()
            I don't think we need it so going without
        */
      
        /*
            We will open the file first, then attempt to read in until the buffer will become full. If it would become full, we output the buffer to the file, and then clear the buffer and
            begin the loop over again.
        */
        
        receiving_file = fopen("fromClient.txt", "w");

        int count, total = 0;

        while ((count = recv(sock_connect, &receive_buf[total], sizeof receive_buf - total, 0)) > 0)
        {
            total += count;

            if ((total >= 4000) || (total + count > BUF_SIZE))
            {
                receive_buf[total] = 0;
                fputs(receive_buf, receiving_file);
                memset(&receive_buf[0], 0, sizeof receive_buf);

                count, total = 0;
            }
        }

        // Regardless of whether we have an error or clean exit, we can simply fputs the buffer to the file and move on for now.
        if (count <= 0)
        {
            fputs(receive_buf, receiving_file);
        }

        // Let us know that the job finished and close our file.
        fprintf(stderr, "Jobs done");
        fclose(receiving_file);

        // Close our socket for the connection
        close(sock_connect);

    }

    return 0;

}
