//
//  main.c
//  serverTCP
//
//  Created by Matthew McCall on 3/21/18.
//  Copyright © 2018 Matthew McCall. All rights reserved.
//
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
    

    struct sockaddr_in servera;
    memset(&servera, 0, sizeof(servera));
    servera.sin_family = AF_INET;
    
    // transforms a value in host byte
    // network byte ordering format
    servera.sin_port = htons(SERVER_PORT);
    
    // same as htons but to long
    servera.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // create a TCP socket
    int listen_sock;
    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("couldn't make listen socket\n");
        return 1;
    }
    
    // bind it to listen to the incoming connections on the created server
    // address, will return -1 on error
    if ((bind(listen_sock, (struct sockaddr *)&servera,
              sizeof(servera))) < 0) {
        printf("couldn't bind socket to address\n");
        return 1;
    }
    
    int wait_size = 16;  // maximum number of waiting clients, after which
    // dropping begins
    if (listen(listen_sock, wait_size) < 0) {
        printf("couldn't open socket \n");
        return 1;
    }
    
    // socket address used to store client address
    struct sockaddr_in client_address;
    int client_address_len = 0;
    
    while (true) {
        // open new socket
        int sck;
        if ((sck =
             accept(listen_sock, (struct sockaddr *)&client_address,
                    &client_address_len)) < 0) {
                 printf("could not open a socket to accept data\n");
                 return 1;
             }
        
        int n = 0;
        int len = 0, maxlen = 100;
        char buffer[maxlen];
        char *pbuffer = buffer;
        
        printf("client connected: %s\n",
               inet_ntoa(client_address.sin_addr));
        
        // keep running as long as the client keeps the connection open
        while ((n = recv(sck, pbuffer, maxlen, 0)) > 0) {
            pbuffer += n;
            maxlen -= n;
            len += n;
            
            printf("received: '%s'\n", buffer);
            
            char *string = buffer;
            while(*string){
                *string = toupper((unsigned char) *string);
                string++;
            }
            // echo received content back
            send(sck, buffer, len, 0);
        }
        
        close(sck);
    }
    
    close(listen_sock);
    return 0;
}
