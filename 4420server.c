#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>

#define SERVER_PORT 4220        /* Opening the port on 4220 as it has no 
                                    assignments that is standardized */
#define BUF_SIZE 4096           /* Block transfer size */
#define QUEUE_SIZE 10

struct sockaddr_in { 
    short sin_family; // e.g. AF_INET 
    unsigned short sin_port; // e.g. htons(3490) 
    struct in_addr sin_addr; // see struct in_addr below 
    char sin_zero[8]; // zero this if you want to 
}; 

int main(void){

    struct sockaddr_in local_addr;   /* addr structs */
    int socknet;                        /* socket */


    socknet = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_net < 0){
        printf("Hey we're getting an error here!");
    }

    
    
    memset(&local_addr, 0, sizeof(local_addr));




}
