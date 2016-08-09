#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int connect_to_host(void *addr_value, int type)
{
        static const unsigned short PORT = 80;
        static const unsigned int REPLY_SIZE = 6000;
        static const int SOCK_TYPE = SOCK_STREAM;

        int socket_endp;
        char pres_ip[INET6_ADDRSTRLEN];
        char *message;
        char server_reply[REPLY_SIZE];
        int buf_size;

        /* Get the presentational value of the IP */
        inet_ntop(type, addr_value, pres_ip, sizeof(pres_ip));
        printf("Connecting to %s...\n", pres_ip);

        /* Build the socket endp */
        socket_endp = socket(type, SOCK_TYPE, 0);
        if(socket_endp == -1){
                puts("Error: Problem establishing socket");
                exit(EXIT_FAILURE);
        }
        else{
                puts("Established socket endpoint");
        }

        /* Establish the connection */
        if(connect(socket_endp, addr_value, sizeof(addr_value)) != -1){
                puts("Error: Problem establishing connection");
                exit(EXIT_FAILURE);
        }
        else{
                puts("Established connection\n\n");
        }

        /* Build message */

        return 1;
}