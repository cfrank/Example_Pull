#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

int connect_to_host(struct addrinfo *addr_i)
{
        static const unsigned short PORT = 80;
        static const unsigned int REPLY_SIZE = 6000;
        static const int SOCK_TYPE = SOCK_STREAM;

        int socket_endp;
        char *message;
        char server_reply[REPLY_SIZE];
        struct sockaddr *peer_addr;
        socklen_t peer_addr_len = sizeof(struct sockaddr);

        /* Build the socket */
        socket_endp = socket(addr_i->ai_family, SOCK_TYPE, addr_i->ai_protocol);
        if(socket_endp == -1){
                puts("Error: Could not create socket");
                return -1;
        }
        else{
                puts("Established socket...");
        }

        /* Connect to the host */
        if(connect(socket_endp, addr_i->ai_addr, addr_i->ai_addrlen) == -1){
                int errev = errno;
                printf("Error: %d\n", errev);
                return -1;
        }
        else{
                puts("Established connection...");
        }

        /* Get the peer name */
        if(getpeername(socket_endp, peer_addr, &peer_addr_len) == -1){
                puts("Error: Error obtaining peer information");
                return -1;
        }
        else{
                printf("Established peer name...\n");
        }

        close(socket_endp);

        return 1;
}