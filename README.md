# CS4420-Project1

## Introduction
This project was completed by Cole Snyder and KC Livingston. We have neither given or received unauthorized assistance on this work.

Our first challenge was how to tackle the project itself given that we had no experience in this area. Therefore, we started with what the book contained. We also individually researched several resources below, including the MAN pages of header files we would need, so that we could better understand how the socket works, how to establish the client-server connection, and how to send information through it.

During our first few iterations of the client and server, we had numerous small bugs that we got stuck up and forced us to go back and reference our resources. Eventually, we discovered Beej's Guide to Network Programming, which described each step in more detail than any other resource we had found. Using this, we discovered that the book's example code was an older method of achieving the results necessary to form the connection, and may be causing some issues with clarity. We chose to strip away some of the unnecessary details such as calling main with arguments in favor of standard input and simple methods we could more easily debug.

Finally, we chose to have our server echo back a message with a changed output, which would help us have a baseline for the file transfer in the next project. Since we split the project down the middle with KC working on the client and Cole on the server, this allowed us both to gain experience with communicating so that we would be able to manage it and have minimal changes for the next assignment.

## Usage
In order to compile the files, simply run
> gcc "filename of input" -o "filename you want"

For example:
> gcc 4220server.c -o 4220Server

Then, the server can be ran through commandline with './4220Server'

This socket was developed for Linux without using the window socket packages, so it is likely to not work or have unexpected behavior on Windows. The socket listens on port 4220.
The client has prompts for when it expects an input.


## Resources
- [Tanenbaum, A. S., Feamster, N., and Wetherall, D. (2021). Computer networks. Pearson. 
Sections:  6.1.3 Berkeley Sockets; 6.1.4 An Example of Socket Programming: An Internet File 
Server; 6.5.2 The TCP Service Model]
- [Beginner's guide to socket programming](https://dev.to/sanjayrv/a-beginners-guide-to-socket-programming-in-c-5an5)
- [sys_socket.h MAN page](https://man7.org/linux/man-pages/man0/sys_socket.h.0p.html)
- [Geek for Geeks, socket programming for client and server](https://www.geeksforgeeks.org/socket-programming-cc/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/split/index.html)
