# CS4220-Project2

## Introduction
This project was completed by Cole Snyder and KC Livingston. We have neither given or received unauthorized assistance on this work.

For the server, we chose to have a hard-coded file that it would write anything that was received. In order to ensure the file would be read correctly, we also chose a system where we would read until the buffer was full, write the buffer into the file and then continue reading and writing as necessary. When we have finished reading in, the server sends a message of confirmation to the client.

The client also has a hard-coded file, "test.txt" and requires no additional input. After exchanging the file, the server remains open for additional connections while the client exits.

## Usage
In order to compile the files, simply run
> gcc "filename of input" -o "filename you want"

For example:
> gcc 4220Server2.c -o 4220Server2
> gcc 4220client2.c -o 4220Client2

Then, the server can be ran through commandline with './4220Server2' and './4220Client2'

This socket was developed for Linux without using the Windows socket packages, so it is likely to not work or have unexpected behavior on Windows. The socket listens on port 4220.
The client has prompts for when it expects an input.


## Resources
- [Tanenbaum, A. S., Feamster, N., and Wetherall, D. (2021). Computer networks. Pearson. 
Sections:  6.1.3 Berkeley Sockets; 6.1.4 An Example of Socket Programming: An Internet File 
Server; 6.5.2 The TCP Service Model]
- [Beginner's guide to socket programming](https://dev.to/sanjayrv/a-beginners-guide-to-socket-programming-in-c-5an5)
- [sys_socket.h MAN page](https://man7.org/linux/man-pages/man0/sys_socket.h.0p.html)
- [Geek for Geeks, socket programming for client and server](https://www.geeksforgeeks.org/socket-programming-cc/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/index.html)
