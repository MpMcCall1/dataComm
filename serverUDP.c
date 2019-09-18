//
//  Created by Matthew McCall on 3/21/18.
//  Copyright © 2018 Matthew McCall. All rights reserved.
//  References https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[]) {
    // port to start
    int SERVER_PORT = atoi(argv[1]);
    
    
    struct sockaddr_in myaddr;      /* our address */
    struct sockaddr_in remaddr;     /* remote address */
    socklen_t addrlen = sizeof(remaddr);            /* length of addresses */
    int recvlen;                    /* # bytes received */
    int fd;
    int maxlen = 100;/* our socket */
    char buf[maxlen];     /* receive buffer */
    
    /* create a UDP socket */
    
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket\n");
        return 0;
    }
    
    /* bind the socket to any valid IP address and a specific port */
    
    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(SERVER_PORT);
    
    if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        perror("bind failed");
        return 0;
    }
    
    /* now loop, receiving data and printing what we received */
    for (;;) {
        printf("waiting on port %d\n", SERVER_PORT);
        recvlen = recvfrom(fd, buf, 2048, 0, (struct sockaddr *)&remaddr, &addrlen);
        printf("received %d bytes\n", recvlen);
        if (recvlen > 0) {
            buf[recvlen] = 0;
            }
        printf("received message: \"%s\"\n", buf);
        char *string = buf;
        while(*string){
            *string = toupper((unsigned char) *string);
            string++;
        }
        printf("changed message: \"%s\"\n", buf);

    }
        }
    /* never exits */
