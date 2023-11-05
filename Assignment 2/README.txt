CMPT300E1 Assignment 2 - due Thursday, October 26, 2023
Submitted By : Rebecca Reedel (Student No. 301454910), Asmita Srivastava (Student No. 301436340)

README file describing our approach and solutions to the assignment 2. 

This week's assignment was based on Sockets and Network Programming using thread programming and sockets as a bridge between 2 processes. The assignment solution was achieved by watching through the cmpt300 workshops by Professor Brian Fraser and reading the manual pages. We started our approach by researching fgets, fputs and other file I/O operations in C. Moreover, both of us also tried to follow through with the documentation on Beej's guide to network programming, in there we found a lot of help regarding syntax usage and data transmission between host and remote servers by using getaddrinfo() etc. 

Following through the video workshops, we were able to implement and understand pthreads in C, including thread creation, thread join and shutdown operations. Professor Brian Fraser also helped understand the critical section problem and how to resolve the critical sections in our application by using conditional varibales and mutual expressions. Using these, we were able to successfully signal turns and commands between different threads and thus, establish communication between host and remote server. Using the receiver side to receive data using recvfrom() and append message to a List ADT, we were able to use writer threads to dispaly message on screen. Conversely, using sender side to write data sendto() from keyboard and using reader threads to convert keyboard input into message in a List ADT, we were able to set up back-and-forth communication between two peers. 

Commands used to run the code : ./s-talk host_port remote_cpu remote_port
Client side : ./s-talk 6001 asb9838-2u-a01.csil.sfu.ca 6060
Server side : ./s-talk 6060 asb9838nu-a14.csil.sfu.ca 6001
