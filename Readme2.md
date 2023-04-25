# CS4220-Project2

## Introduction
This project was completed by Cole Snyder and KC Livingston. We have neither given or received unauthorized assistance on this work.

For the server, we chose to have a specific file that it would write anything that was received. In order to ensure the file would be read correctly, we also chose a system where we would read until the buffer was full, clear the buffer and place the text so far into the file, and then continue reading as necessary.

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
